#ifndef FONTS_H
#define FONTS_H

//
//	Structure om font te definieren
//
typedef struct {
	const uint8_t FontWidth;    /*!< Font width in pixels */
	uint8_t FontHeight;   /*!< Font height in pixels */
	const uint8_t *data; /*!< Pointer to data font data array */
} FontDef;


//
//	De 3 fonts
//
extern FontDef Font_5x8;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

#endif
