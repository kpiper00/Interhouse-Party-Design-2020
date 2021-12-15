/*******************************************************************************
 * fht_music_60.ino - 60 LED music visualizer with FHT
 *      Author:         Ray Sun 
 *      Last Updated:   2/23/2020
 *
 * Description:
 *      This is a simple Arduino sketch for the Bifrost addressable RGB 
 *      LED controller that lights an individually addressable (WS8211 /  WS282b) 
 *      RGB LED strip of 60 LEDs in a rainbow spectrum, from red 
 *      (data in) to violet (data out), with the brightness of each individual 
 *      LED controlled by the frequency spectrum of audio input through an 
 *      audio jack.
 *
 * Interface:
 *      Input       Audio L input       Line level audio in
 *      Output      Output 1,2          LED strip output 1,2
 *
 * Hardware:
 *      Bifrost
 *
 * Revision History:
 *      12/31/2018      Ray Sun         Initial revision. 
 *      1/1/2019        Ray Sun         Changed to linear scale for better 
 *                                      visual result.
 *      4/3/2019        Ray Sun         Refactored to use FastLED library.
 *      5/25/2019       Ray Sun         Migrate to audio input.
 *      5/28/2019       Ray Sun         Perfect 150 LED setup.
 *      2/20/2020       Ray Sun         Adapt to run on Bifrost.
 *      2/23/2020       Ray Sun         Adapt to run 60 LEDs.
 *
 * Validation:
 *      2/23/2020       Ray Sun         Validated.
 ******************************************************************************/
 

#include <avr/pgmspace.h>                   // For constants in SRAM
#include <FastLED.h>
#include <Heimdall.h>


// System constants
#define     N_LEDS              150         // Number of LEDs / pixels
#define     START_DEL_MS        2000        // Startup delay

// LED constants
#define     ONE_8               0xFF
#define     COLOR_WHITE         0x56587F    // Given in Adafruit FFT code     

// FHT configuration
#define     LIN_OUT             1           // Use the linear output function
#define     FHT_N               256         // Number of FFT bins


#include <FHT.h> 


// Spectrum constants 
#define     N_INTBINS           20          // Number of FHT bins used
#define     N_INTERPOLATE       3           // Number of LEDs per FHT bin
#define     SPEC_START          2           // # bin to use as the start
                                            // of the spectrum for the LEDs

// Intensity constants 
#define     INT_MIN             10
#define     INT_MAX             255
#define     INT_SR              1           // Rightshift intensity 
#define     INT_OFF             25          // then subtract baseline

// Hue constants 
//      Compute with ~ H_TOP_VAL (255) / N_LEDS 
#define     H_MUL               7           // Multiplicative factor
#define     H_SR                1           // Rightshift factor

    
// Strip object
CRGB leds[N_LEDS];

// Intensities for FHT bins
int intensities[N_INTBINS + 1];


void setup() {
    // Wait a bit with everything off
    delay(START_DEL_MS);
    
    // Initialize and clear the strip
    FastLED.addLeds<NEOPIXEL, 5>(leds, N_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<NEOPIXEL, 6>(leds, N_LEDS).setCorrection( TypicalLEDStrip );
    
    // Set up left audio for analog in
    TIMSK0 = 0;             // Disable timer 0 for lower jitter

    hmd_adc_init();
    hmd_adc_source(AUD_L);
}

void loop() {
    while(1) {                  // Reduce jitter
  
        cli();                  // Disable interrupts
    
        // Acquire FHT input - `FHT_N` number of samples
        hmd_adc_read(fht_input, FHT_N);
        
        // Do the FHT:
        fht_window();       // Window the data for better frequency response
        fht_reorder();      // Reorder the data before doing the FHT
        fht_run();          // Process the data in the FHT
        fht_mag_lin();      // Take the output of the FHT
        
        sei();              // Re-enable interrupts
        
        // Now light the LEDs accordingly
        
        for (uint8_t bin = 0; bin <= N_INTBINS; bin ++) {
            // Compute the pixel value (average among bins)
            uint8_t fht_bin = SPEC_START + bin;
            
            // Compute the intensity: 
            //      ( (sum / range) >> shift factor ) - baseline
            intensities[bin] = (fht_lin_out[fht_bin] >> INT_SR) - INT_OFF; 
            
            // Finally, send to the strip 
            //      Hue             pixel position * scale
            //      Sat             1
            //      Brightness      computed intensity
            if (intensities[bin] < INT_MIN)
                leds[bin * N_INTERPOLATE] = CRGB::Black;
            else if (intensities[bin] > INT_MAX)
                leds[bin * N_INTERPOLATE] = CRGB::White;
            else
                leds[bin * N_INTERPOLATE] = 
                    CHSV( (bin * N_INTERPOLATE * H_MUL) >> H_SR, 
                          ONE_8, intensities[bin]);
        }

        // Linear interpolate intensity
        for (uint8_t bin = 0; bin < N_INTBINS; bin++) {
            for (uint8_t px = 1; px < N_INTERPOLATE; px++) {
                int intensity = ( ((N_INTERPOLATE - px) * intensities[bin]) + 
                                  (px * intensities[bin+1]) ) / N_INTERPOLATE;
                if (intensity < INT_MIN)
                    leds[(bin * N_INTERPOLATE) + px] = CRGB::Black;
                else if (intensity > INT_MAX)
                    leds[(bin * N_INTERPOLATE) + px] = CRGB::White;
                else
                    leds[(bin * N_INTERPOLATE) + px] = 
                        CHSV(( ((bin * N_INTERPOLATE) + px) * H_MUL) >> H_SR, ONE_8, intensity);
            }
        }
        
        // Once done setting the intensities, refresh the strip
        FastLED.show();
    }
}
