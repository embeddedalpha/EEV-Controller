/*
 * R454B.h
 *
 *  Created on: Sep 16, 2024
 *      Author: kunal
 */

#ifndef R454B_R454B_H_
#define R454B_R454B_H_

#define R545B_Table_Size 57

// Structure to store pressure and temperature data
typedef struct {
    int pressure;     // Pressure in PSIG
    float temp_avg;   // Average Temperature in Fahrenheit (°F)
} R454B_PressureTempEntry;


R454B_PressureTempEntry R454B_Saturation_Table[R545B_Table_Size] = {
	    {0, -58.1}, {20, -24.3}, {40, -3.6}, {60, 11.9}, {70, 18.5},
	    {80, 24.5}, {90, 30.0}, {95, 32.7}, {100, 35.2}, {105, 37.7},
	    {110, 40.0}, {115, 42.3}, {120, 44.6}, {125, 46.7}, {130, 48.9},
	    {135, 50.9}, {140, 52.9}, {145, 54.9}, {150, 56.8}, {155, 58.7},
	    {160, 60.5}, {170, 64.1}, {180, 67.5}, {190, 70.8}, {200, 73.9},
	    {210, 77.0}, {220, 80.0}, {240, 85.6}, {260, 90.9}, {270, 93.4},
	    {280, 95.9}, {290, 98.3}, {300, 100.7}, {310, 103.0}, {320, 105.2},
	    {330, 107.4}, {340, 109.6}, {345, 110.7}, {350, 111.7}, {355, 112.7},
	    {360, 113.8}, {365, 114.8}, {370, 115.8}, {375, 116.8}, {380, 117.8},
	    {385, 118.7}, {390, 119.7}, {395, 120.7}, {400, 121.6}, {405, 122.5},
	    {410, 123.5}, {415, 124.4}, {420, 125.3}, {425, 126.2}, {430, 127.1},
	    {435, 128.0}, {440, 128.9}, {445, 129.8}, {450, 130.6}, {460, 132.3},
	    {470, 134.0}, {480, 135.7}, {490, 137.3}, {500, 138.9}, {510, 140.5},
	    {520, 142.1}, {530, 143.6}
	};




#endif /* R454B_R454B_H_ */
