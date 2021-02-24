#include "avif/avif.h"
#include <stdint.h>

int avif_decode(uint8_t* src, int src_len, uint8_t** dst, int* dst_len, int* width, int* height) {
    int ret_code = 0;
    avifDecoder* decoder = avifDecoderCreate();
    avifRGBImage rgb;
    avifResult result = avifDecoderSetIOMemory(decoder, src, src_len);
    if (result != AVIF_RESULT_OK) {
        ret_code = -1;
        goto end;
    }

    result = avifDecoderParse(decoder);
    if (result != AVIF_RESULT_OK) {
        ret_code = -2;
        goto end;
    }

    *width = decoder->image->width;
    *height = decoder->image->height;

    result = avifDecoderNextImage(decoder);
    if (result != AVIF_RESULT_OK) {
        ret_code = -3;
        goto end;
    }
    
    avifRGBImageSetDefaults(&rgb, decoder->image);
    avifRGBImageAllocatePixels(&rgb);

    if (avifImageYUVToRGB(decoder->image, &rgb) != AVIF_RESULT_OK) {
        ret_code = -4;
        goto end;
    }

    *dst_len = rgb.rowBytes * rgb.height;
    *dst = rgb.pixels;

end:
    avifDecoderDestroy(decoder);
    return ret_code;
}
