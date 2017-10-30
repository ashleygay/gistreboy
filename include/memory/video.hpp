#pragma once

#include <array>
#include <vector>
#include <string>
#include <memoryobject.hpp>

class Video : public MemoryObject {

public :

	Video() {}

 	Video(Processor* proc,
	      std::vector<std::pair<uint16_t, uint16_t>> rang);

	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t byte);

	// FIXME: actually implement permissions
	bool can_read(uint16_t address);
	bool can_write(uint16_t address, uint8_t byte);

	uint8_t get_lcd_control();
	uint8_t get_lcd_status();
	uint8_t get_scrolly();
	uint8_t get_scrollx();
	uint8_t get_ly();
	uint8_t get_lyc();
	uint8_t get_wy();
	uint8_t get_wx(); /* actually wx - 7 */
	uint8_t get_bgp();
	uint8_t get_obp0();
	uint8_t get_obp1();
	

private :

	std::array<uint8_t, 0x10000> video_memory;
};
