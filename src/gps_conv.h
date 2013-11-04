#ifndef GPS_CONV_H
#define GPS_CONV_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#define MAX_STR_LEN 128
#define PI 3.141592653589793
#define EARTH_RADIUS 6371000 //meters (average earth radius)

/* warning : approximations
 * approximation due to consideration of shperical earth
 * and to approximated values (pi, earth radius...)
 */

typedef struct StructGeoPoint{
	double latitude;
	double longitude;
}GeoPoint;

/*typedef struct StructLocalizationMeasure{
	char name[MAX_STR_LEN];
	GeoPoint * localizations;
	double * measureTimes;
	size_t n_measures;
}LocalizationMeasure;
*/

/** converts from format dddmm.mmmm to radians
 */
double degreesMinutesToDegrees(double value);

GeoPoint analyseGpsGga(char * data);

double distance(const GeoPoint *a, const GeoPoint *b);
#endif // GPS_CONV_H
