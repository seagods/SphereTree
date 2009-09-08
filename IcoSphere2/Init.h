
typedef unsigned char byte;
int VideoFlags=0;
SDL_Surface * MainWindow=NULL;
/*   ************************************************** */    
void ToggleFullScreen(void){
     if(SDL_WM_ToggleFullScreen(MainWindow) == 0){
           std::cout <<  "Failed during screen toggle";
           SDL_Quit();
           exit(0);
           }
}

void MakeWindow(const char *name, int width, int height, int VideoFlags){
  MainWindow=SDL_SetVideoMode(width, height, SCREEN_DEPTH, VideoFlags);
  if(MainWindow==NULL){
                  std::cout <<  "Failed at MakeWindow\n";
                  SDL_Quit();
                  exit(0);
                  }
}

int main()
{
    using namespace std;
    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    SetUp();
    //cout << "Video Flags=" << VideoFlags << "\n";
    MakeWindow("A Window", SCREEN_WIDTH, SCREEN_HEIGHT, VideoFlags);
    SizeOpenGLScreen(width, height);
   // std::cout <<  " Calling Constructor for CCam Cammera1\n";   
    CCam Camera1;
    Init();
    EventLoop(Camera1);
    return 0;
}

void SetUp(){

VideoFlags=SDL_OPENGL;
VideoFlags |= SDL_HWPALETTE;
VideoFlags |=SDL_RESIZABLE;

const SDL_VideoInfo *VidInfo=SDL_GetVideoInfo();
if(VidInfo==NULL){
      std::cout << " failed to get video information\n";
      SDL_Quit();
      exit(0);
      }



if(VidInfo->hw_available){
        VideoFlags |=SDL_HWSURFACE;
       std::cout << "Hardware Available\n";
        }
      else
        {
         VideoFlags |=SDL_SWSURFACE;
       std::cout << "Hardware not Available, using software\n";
        }
if(VidInfo->blit_hw)
    VideoFlags |=SDL_HWACCEL;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, SCREEN_DEPTH);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);
}
void SizeOpenGLScreen(int width, int height){

  if(height==0){
      std::cout << "Height is zero, abandon ship!\n";
      SDL_Quit();
      exit(0);
      }

      std::cout <<  "height=" << height << "  width=" << width << "\n";
      glViewport(0,0,width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(45.0f,(GLfloat)width/GLfloat(height), 100.0f, 150000.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

}

void InitialiseGL(int width, int height){
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_TEXTURE_2D);
    SizeOpenGLScreen(width, height);

}

static void swap(unsigned char &a ,unsigned char &b)
{unsigned char temp;
temp=a;
a=b;
b=temp;
return;
}
// The following is a straight copy of Digital Ben's routine from TextureMapping
/////////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////  This creates a texture in OpenGL that we can texture map
/////
/////////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CreateTexture(unsigned int textureArray[],char *strFileName,int textureID)
{
    SDL_Surface *pBitmap[1];

    if( strFileName == NULL )                           // Return from the function if no file name was passed in
        return ;

    // We need to load the texture data, so we use a cool function that SDL offers.

    pBitmap[0] = SDL_LoadBMP(strFileName);              // Load the bitmap and store the data

    if(pBitmap[0] == NULL)                                // If we can't load the file, quit!
    {
        std::cout << " Failed loading " << strFileName << " : " << SDL_GetError() << "\n";
        exit(0);
    }

    // Now that we have the texture data, we need to register our texture with OpenGL
    // To do this we need to call glGenTextures().  The 1 for the first parameter is
    // how many texture we want to register this time (we could do a bunch in a row).
    // The second parameter is the array index that will hold the reference to this texture.

    // Generate a texture with the associative texture ID stored in the array
    glGenTextures(1, &textureArray[textureID]);

    // Now that we have a reference for the texture, we need to bind the texture
    // to tell OpenGL this is the reference that we are assigning the bitmap data too.
    // The first parameter tells OpenGL we want are using a 2D texture, while the
    // second parameter passes in the reference we are going to assign the texture too.
    // We will use this function later to tell OpenGL we want to use this texture to texture map.

    // Bind the texture to the texture arrays index and init the texture
    glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

    // WARNING   : GO THROUGH THESE FEW LINES FOR SWAPPING ROWS ONLY IF YOU REALLY NEED TO, OR ELSE SKIP
    // THE LINES MARKED BELOW. Just take it for granted that these lines of code swap rows in the texture
    // as required by us.

    // <SKIP> <SKIP> <SKIP> <SKIP>   (FROM HERE)        -------------------
    //
    // IMPORTANT : SDL loads Bitmaps differently when compared to the default windows loader. The row 0
    // corresponds to the top row and NOT the bottom row. Therefore if we don't invert the order of the rows,
    // then the textures will appear (vertically) inverted.
    // Therefore we must reverse the ordering of the rows in the data of the loaded surface ( the member
    //  'pixels' of the structure)

    // Rearrange the pixelData

    int width  = pBitmap[0] -> w;
    int height = pBitmap[0] -> h;
    unsigned char * data = (unsigned char *) (pBitmap[0] -> pixels);         // the pixel data
    unsigned char * newData = new unsigned char[width*height*3];
    int channels = 3; // R,G,B

    int BytesPerPixel = pBitmap[0] -> format -> BytesPerPixel ;

    //////////// This is how we swap the rows :
    // For half the rows, we swap row 'i' with row 'height - i -1'. (if we swap all the rows
    // like this and not the first half or the last half, then we get the same texture again !
    //
    // Now these rows are not stored as 2D arrays, instead they are stored as a long 1D array.
    // So each row is concatenated after the previous one to make this long array. Our swap
    // function swaps one byte at a time and therefore we swap BytesPerPixel (= total bits per pixel)
    // bytes succesively.
    //
    // so the three loops below are :
    // for the first half of the rows
    //   for all the width (which is width of image * BytesPerPixel, where BytesPerPixel = total bits per pixel).
    //   (Here, for each pixel, we have to increment j by total bits per pixel (to get to next pixel to swap))
    //      for(each byte in this pixel i.e k = 0 to BytesPerPixel - 1, i.e BytesPerPixel bytes.
    //        swap the byte with the corresponding byte in the 'height -i -1'th row ('i'th row from bottom)
    for( int i = 0 ; i < (height / 2) ; ++i )
        for( int j = 0 ; j < width * BytesPerPixel; j += BytesPerPixel )
            for(int k = 0; k < BytesPerPixel; ++k)
                swap( data[ (i * width * BytesPerPixel) + j + k], data[ ( (height - i - 1) * width * BytesPerPixel ) + j + k]);

    // </SKIP> </SKIP> </SKIP> </SKIP>    (TO HERE)   -------------------

    // the following lines extract R,G and B values from any bitmap

    for(int i = 0; i < (width * height); ++i)
    {
        byte r,g,b;                                                // R,G and B that we will put into pImage

        Uint32 pixel_value = 0;                                    // 32 bit unsigned int (as dictated by SDL)

        // the following loop extracts the pixel (however wide it is 8,16,24 or 32) and
        // creates a long with all these bytes taken together.

        for(int j = BytesPerPixel - 1 ; j >=0; --j)                // for each byte in the pixel (from the right)
        {
            pixel_value = pixel_value << 8;                        // left shift pixel value by 8 bits
            pixel_value = pixel_value | data[ (i * BytesPerPixel) + j ];  // then make the last 8 bits of pixel value  =
        }                                                                 // the byte that we extract from pBitmap's data

        SDL_GetRGB(pixel_value, pBitmap[0] -> format, (Uint8 *)&r, (Uint8 *)&g, (Uint8 *)&b);     // here we get r,g,b from pixel_value which is stored in the form specified by pBitmap->format

        newData[(i * channels) + 0] = r;          // in our tImage classes we store r first
        newData[(i * channels) + 1] = g;          // then g
        newData[(i * channels) + 2] = b;          // and finally b (for bmps - three channels only)

        pixel_value = 0;                                           // reset pixel , else we get incorrect values of r,g,b
    }


    // Now comes the important part, we actually pass in all the data from the bitmap to
    // create the texture. Here is what the parameters mean in gluBuild2DMipmaps():
    // (We want a 2D texture, 3 channels (RGB), bitmap width, bitmap height, It's an RGB format,
    //  the data is stored as unsigned bytes, and the actuall pixel data);

    // What is a Mip map?  Mip maps are a bunch of scaled pictures from the original.  This makes
    // it look better when we are near and farther away from the texture map.  It chooses the
    // best looking scaled size depending on where the camera is according to the texture map.
    // Otherwise, if we didn't use mip maps, it would scale the original UP and down which would
    // look not so good when we got far away or up close, it would look pixelated.

    // Build Mipmaps (builds different versions of the picture for distances - looks better)

    // Build Mipmaps (builds different versions of the picture for distances - looks better)
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap[0]->w, pBitmap[0]->h, GL_RGB, GL_UNSIGNED_BYTE, newData);

    // Lastly, we need to tell OpenGL the quality of our texture map.  GL_LINEAR_MIPMAP_LINEAR
    // is the smoothest.  GL_LINEAR_MIPMAP_NEAREST is faster than GL_LINEAR_MIPMAP_LINEAR,
    // but looks blochy and pixilated.  Good for slower computers though.  Read more about
    // the MIN and MAG filters at the bottom of main.cpp
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);

    // Now we need to free the bitmap data that we loaded since openGL stored it as a texture
    delete [] newData;

    SDL_FreeSurface(pBitmap[0]);                        // Free the texture data we dont need it anymore
}


/*Thanks to Andreas Umbach and Pete Shinners about the
Screenshot routine written by Ray Kelm. It works
very well, I'm very happy.

I had to make a small modification to pass the screen
as an argument, so here's my version of Screenshot: */

int Screenshot(SDL_Surface *screen, char *filename)
{
        SDL_Surface *temp;
        unsigned char *pixels;
        int i;

        if (!(screen->flags & SDL_OPENGL)) {
                SDL_SaveBMP(temp, filename);
                return 0;
        }

        temp = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                    screen->w, screen->h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
        0x000000FF, 0x0000FF00, 0x00FF0000, 0
#else
        0x00FF0000, 0x0000FF00, 0x000000FF, 0
#endif
        );
        if (temp == NULL) return -1;

        pixels =(unsigned char*) malloc(3 * screen->w * screen->h);
        if (pixels == NULL) {
                SDL_FreeSurface(temp);
                return -1;
        }

        glReadPixels(0, 0, screen->w, screen->h,
                     GL_RGB, GL_UNSIGNED_BYTE, pixels);

        for (i=0; i<screen->h; i++)
                memcpy(((char *) temp->pixels) + temp->pitch * i,
                       pixels + 3*screen->w * (screen->h-i-1),
                       screen->w*3);
        free(pixels);

        SDL_SaveBMP(temp, filename);
        SDL_FreeSurface(temp);
        return 0;
}

//Thanks again
//Marc
