#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


struct digimon
{
  SDL_Rect box;
  int64_t evolutions;
  bool canSelect;
};

void SDL_start();
void texture_load();
bool box_click(SDL_Rect *mouse, SDL_Rect *box);
void selectDigimons(struct digimon dig[], int8_t size, int8_t first);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main(int argc, char* args[] )
{

  // tell gcc those variables
  // are not being used
  // SDL2 requires you have them on main
  (void)argc;
  (void)args;

  const uint8_t DIGIMONS = 61;
  const uint8_t BOX = 37;


  const char *image_names[] = {
    "assets/fresh.jpg", "assets/fresh.jpg", "assets/fresh.jpg",
    "assets/fresh.jpg", "assets/agumon.jpg", "assets/gabumon.jpg",
    "assets/patamon.jpg", "assets/elecmon.jpg", "assets/biyomon.jpg",
    "assets/kunemon.jpg", "assets/palmon.jpg", "assets/betamon.jpg",
    "assets/penguinmon.jpg", "assets/greymon.jpg", "assets/monochromon.jpg",
    "assets/ogremon.jpg", "assets/airdramon.jpg", "assets/kuwagamon.jpg",
    "assets/whamon.jpg", "assets/frigimon.jpg", "assets/nanimon.jpg",
    "assets/meramon.jpg", "assets/drimogemon.jpg", "assets/leomon.jpg",
    "assets/kokatorimon.jpg", "assets/vegiemon.jpg", "assets/shellmon.jpg",
    "assets/mojyamon.jpg", "assets/birdramon.jpg", "assets/tyrannomon.jpg",
    "assets/angemon.jpg", "assets/unimon.jpg", "assets/ninjamon.jpg",
    "assets/coelamon.jpg", "assets/numemon.jpg", "assets/centarumon.jpg",
    "assets/devimon.jpg", "assets/bakemon.jpg", "assets/kabuterimon.jpg",
    "assets/seadramon.jpg", "assets/garurumon.jpg", "assets/sukamon.jpg",
    "assets/metalgreymon.jpg", "assets/skullgreymon.jpg", "assets/giromon.jpg",
    "assets/hkabuterimon.jpg", "assets/metalmamemon.jpg", "assets/megaseadramon.jpg",
    "assets/vademon.jpg", "assets/etemon.jpg", "assets/andromon.jpg",
    "assets/megadramon.jpg", "assets/phoenixmon.jpg", "assets/piximon.jpg",
    "assets/mamemon.jpg", "assets/monzaemon.jpg", "assets/digitamamon.jpg",
    "assets/bakemon2.jpg", "assets/help.jpg", "assets/digimonevo.png"
  };

  // to load our images
  SDL_Texture *images[3] = {NULL, NULL, NULL};
  // location and size of the evolution images
  // when rendered on screen
  // also used to display help image
  SDL_Rect evo_image = {50,50,540,380};
  // help box
  SDL_Rect help_box = {38,412, 52, 16};

  bool gameloop = true;
  bool one_selected = false;
  bool two_selected = false;
  bool rectVisible = false;
  bool help = false;

  int8_t first = -1;
  int8_t second = -1;
  int8_t image_location = 0;

  struct digimon digimons[DIGIMONS];

  FILE *fp;
  const char *filename = "assets/digimonboxes.txt";

  if ((fp = fopen(filename, "r")) == NULL) {
    printf("Error. Can't open %s\n", filename);
    exit(EXIT_FAILURE);
  }

  // create boxes for the digimons
  for(int8_t i = 0; i < DIGIMONS; i++) {
    if(fscanf(fp, "%d %d %ld\n", &digimons[i].box.x, &digimons[i].box.y, &digimons[i].evolutions) != 3) {
      printf("Error reading values from %s", filename);
      exit(EXIT_FAILURE);
    }

    digimons[i].box.w = digimons[i].box.h = BOX;
    digimons[i].canSelect = true;
  }

  fclose(fp);

  // SDL stuffs
  SDL_start();

  // background image
  images[0] = IMG_LoadTexture(renderer, image_names[59]);
  if (images[0] == NULL) {
    printf("Error: %s\n", IMG_GetError());
    exit(EXIT_FAILURE);
  }

  // help image
  images[1] = IMG_LoadTexture(renderer, image_names[58]);
  if (images[1] == NULL) {
    printf("Error: %s\n", IMG_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Event e;



  while(gameloop) {

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        gameloop = false;
      // mouse events
      if (e.type == SDL_MOUSEBUTTONDOWN && !two_selected)
        {
          int32_t x,y;
          SDL_GetMouseState(&x, &y);

          // if we clicked on help
          if (box_click(&(SDL_Rect) {x,y,0,0}, &help_box)) {
            help = true;
          }

          // when we click on a digimon
          for(int8_t i = 0; i < DIGIMONS; i++)
            if (box_click(&(SDL_Rect) {x,y,0,0}, &digimons[i].box) &&
                i != first && i != second && !help && digimons[i].canSelect) {
              digimons[i].canSelect = false;
              one_selected = true;
              if (first < 0)
                first = i;
              else {
                second = i;
                two_selected = true;
                one_selected = false;
                // for bakemon in case first digimon is not penguinmon
                if (second == 41 && first != 16)
                  image_location = 57;
                else
                  image_location = second - 4;
              }
            }
        }

      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        for(int8_t i = 0; i < DIGIMONS; i++) {
          digimons[i].canSelect = true;
          first = second = -1;
          if (two_selected){
            SDL_DestroyTexture(images[2]);
            images[2] = NULL;
          }
          rectVisible = one_selected = two_selected = help = false;
        }
      }
    }

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, images[0], NULL, NULL);

    if (one_selected) {
      if (!rectVisible) {
        selectDigimons(digimons, DIGIMONS, first);
        rectVisible = true;
      }
      for (int8_t i = 0; i < DIGIMONS; i++) {
        if (!digimons[i].canSelect && i != first) {
          SDL_SetRenderDrawColor(renderer, 0x87, 0x87, 0x87, 0xFF);
          SDL_RenderFillRect(renderer, &digimons[i].box);
        }
      }
    } else if (two_selected) {
      // check if we have not rendered the image yet
      if (images[2] == NULL) {
        images[2] = IMG_LoadTexture(renderer, image_names[image_location]);
        // check if we were able to load texture
        if (images[2] == NULL) {
          printf("Error: %s\n", IMG_GetError());
          exit(EXIT_FAILURE);
        }
      }
       SDL_RenderCopy(renderer, images[2], NULL, &evo_image);
    }
    if (help) {
      SDL_RenderCopy(renderer, images[1], NULL, &evo_image);
    }
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(images[0]);
  SDL_DestroyTexture(images[1]);
  images[0] = NULL;
  images[1] = NULL;
  if (images[2] != NULL)
    SDL_DestroyTexture(images[2]);
  images[2] = NULL;

  SDL_DestroyRenderer(renderer);
  renderer = NULL;

  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();
  return 0;
}

void selectDigimons(struct digimon *dig, int8_t size, int8_t first)
{
  const uint8_t MASK = 0x3F;
  const uint8_t SHIFT = 6;

  for(int8_t i = 0; i < size; i++) {
    dig[i].canSelect = false;
  }

  int64_t evo = dig[first].evolutions;
  /* Our evo variable has a 64 bit number where every 6 bits represents the
  *  position in the digimon array of one of its evolution. So we take every
  *  6 bits using a & MASK, make that digimon selectable in the array
  *  and then remove these 6 bits from the evo variable using a >>= SHIFT. */
  while (evo != 0) {
    dig[evo & MASK].canSelect = true;

    evo >>= SHIFT;
  }

}

void SDL_start()
{
  const uint16_t SCREEN_WIDTH = 640;
  const uint16_t SCREEN_HEIGHT = 480;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  window = SDL_CreateWindow("Digimon Evo Tool", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) {
    printf("Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
    printf("Error: %s\n", IMG_GetError());
    exit(EXIT_FAILURE);
  }
}

bool box_click(SDL_Rect *mouse, SDL_Rect *box)
{
  if (mouse->x >= box->x && mouse->x <= (box->x + box->w) &&
      mouse->y >= box->y && mouse->y <= (box->y + box->h))
    return true;

  return false;
}
