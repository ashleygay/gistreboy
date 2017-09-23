#pragma once

#include <array>
#include <vector>
#include <string>

class Video {

public :
  Video();

  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t byte);

private :

  /* VRAM : 9000-9FFF */
  std::vector<uint8_t> vram;
  /* OAM : FE00-FE9F */
  std::vector<uint8_t> oam;
  
  /* LCD Control : FF40 */
  uint8_t lcd_control;
  /* LCD Status : FF41 */
  uint8_t lcd_status;

  /* LCD Position and SCROLLING */
  /* Scroll y : FF42 */
  uint8_t scroll_y;
  /* Scroll x : FF43 */
  uint8_t scroll_x;
  /* LY (LCDC Y Coordinate): FF44 */
  uint8_t ly;
  /* LYC (LY Compare): FF45 */
  uint8_t lyc;
  /* Window Y : FF4A */
  uint8_t wy;
  /* Window X MINUS 7 : FF4B */
  uint8_t wx;

  /* Palettes */
  /* Background Palette Data : FF47 */
  uint8_t bgp;
  /* Object Palette Data 0 : FF48 */
  uint8_t obp0;
  /* Object Palette Data 1 : FF49 */
  uint8_t obp1;

  /* DMA Transfer : FF46 (very complex, check manual) */
  
  

}
