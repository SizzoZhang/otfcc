#ifndef CARYLL_TABLES_GLYF_H
#define CARYLL_TABLES_GLYF_H

#include <stdint.h>
#include <stdbool.h>
#include "../caryll-font.h"
#include "../extern/sds.h"
#include "../support/glyphorder.h"

enum GlyphType { SIMPLE, COMPOSITE };

typedef struct {
	int16_t x;
	int16_t y;
	int8_t onCurve;
} glyf_point;

typedef struct {
	uint16_t pointsCount;
	glyf_point *points;
} glyf_contour;

typedef struct {
	glyph_reference glyph;
	// transformation term
	float a;
	float b;
	float c;
	float d;
	int16_t x;
	int16_t y;
	bool useMyMetrics;
	bool overlap;
} glyf_reference;

typedef struct {
	uint16_t numberOfContours;
	uint16_t numberOfReferences;
	sds name;

	uint16_t instructionsLength;
	uint8_t *instructions;
	uint16_t advanceWidth;
	union {
		glyf_contour *contours;
		glyf_reference *references;
	} content;
} glyf_glyph;

typedef struct {
	uint16_t numberGlyphs;
	glyf_glyph **glyphs;
} table_glyf;

#define GLYF_FLAG_ON_CURVE 1
#define GLYF_FLAG_X_SHORT (1 << 1)
#define GLYF_FLAG_Y_SHORT (1 << 2)
#define GLYF_FLAG_REPEAT (1 << 3)
#define GLYF_FLAG_SAME_X (1 << 4)
#define GLYF_FLAG_SAME_Y (1 << 5)
#define GLYF_FLAG_POSITIVE_X (1 << 4)
#define GLYF_FLAG_POSITIVE_Y (1 << 5)

#define ARG_1_AND_2_ARE_WORDS (1 << 0)
#define MORE_COMPONENTS (1 << 5)
#define WE_HAVE_A_SCALE (1 << 3)
#define WE_HAVE_AN_X_AND_Y_SCALE (1 << 6)
#define WE_HAVE_A_TWO_BY_TWO (1 << 7)
#define WE_HAVE_INSTRUCTIONS (1 << 8)

glyf_glyph *spaceGlyph();
void caryll_read_glyf(caryll_font *font, caryll_packet packet);

#endif
