#include <iostream>
#include <stdio.h>
#include <string.h>
#include <OpenImageIO/imageio.h>
#include <OpenImageIO/imagebuf.h>

OIIO_NAMESPACE_USING;
using namespace std;

#define RED 0xFF0000FF
#define GRN 0xFF00FF00
#define BLU 0xFFFF0000
#define CYN 0xFFFFFF00
#define YLW 0xFF00FFFF
#define MGN 0xFFFF00FF
#define BLK 0xFF000000
#define GRY 0xFF888888
#define WHT 0xFFFFFFFF

int main( int argc, char *argv[] )
{
    int size =  256;
    int types = 8;
    if( argc > 1 ) types = atoi( argv[1] );
    if( argc > 2 ) size = atoi( argv[2] );
    ImageSpec spec(size,size,4, TypeDesc::UINT8);
    ImageBuf *buf = new ImageBuf("file", spec);

    unsigned int* pixel_data = (unsigned int *)buf->localpixels();

    int tl,tr,bl,br;  //pixel locations; top left, top right etc;
    int tile = 0;
    for( tl = 0; tl < types; ++tl )
    for( tr = 0; tr < types; ++tr )
    for( bl = 0; bl < types; ++bl )
    for( br = 0; br < types; ++br ){
        //0=r,1=g,2=b,3=a
        int offset = tile * 2 + tile / (size / 2 ) * size;
        if(tl == 0) pixel_data[ offset ] = RED;
        if(tl == 1) pixel_data[ offset ] = GRN;
        if(tl == 2) pixel_data[ offset ] = BLU;
        if(tl == 3) pixel_data[ offset ] = CYN;
        if(tl == 4) pixel_data[ offset ] = YLW;
        if(tl == 5) pixel_data[ offset ] = MGN;
        if(tl == 6) pixel_data[ offset ] = BLK;
        if(tl == 7) pixel_data[ offset ] = GRY;
        if(tl == 8) pixel_data[ offset ] = WHT;

        ++offset;
        if(tr == 0) pixel_data[ offset ] = RED;
        if(tr == 1) pixel_data[ offset ] = GRN;
        if(tr == 2) pixel_data[ offset ] = BLU;
        if(tr == 3) pixel_data[ offset ] = CYN;
        if(tr == 4) pixel_data[ offset ] = YLW;
        if(tr == 5) pixel_data[ offset ] = MGN;
        if(tr == 6) pixel_data[ offset ] = BLK;
        if(tr == 7) pixel_data[ offset ] = GRY;
        if(tr == 8) pixel_data[ offset ] = WHT;

        offset += size -1;
        if(bl == 0) pixel_data[ offset ] = RED;
        if(bl == 1) pixel_data[ offset ] = GRN;
        if(bl == 2) pixel_data[ offset ] = BLU;
        if(bl == 3) pixel_data[ offset ] = CYN;
        if(bl == 4) pixel_data[ offset ] = YLW;
        if(bl == 5) pixel_data[ offset ] = MGN;
        if(bl == 6) pixel_data[ offset ] = BLK;
        if(bl == 7) pixel_data[ offset ] = GRY;
        if(bl == 8) pixel_data[ offset ] = WHT;

        ++offset;
        if(br == 0) pixel_data[ offset ] = RED;
        if(br == 1) pixel_data[ offset ] = GRN;
        if(br == 2) pixel_data[ offset ] = BLU;
        if(br == 3) pixel_data[ offset ] = CYN;
        if(br == 4) pixel_data[ offset ] = YLW;
        if(br == 5) pixel_data[ offset ] = MGN;
        if(br == 6) pixel_data[ offset ] = BLK;
        if(br == 7) pixel_data[ offset ] = GRY;
        if(br == 8) pixel_data[ offset ] = WHT;

        ++tile;

    }

    buf->write("test.tif");
    cout << tile << endl;
    return 0;
}
