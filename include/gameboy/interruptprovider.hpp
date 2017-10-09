/*
 * File : interruptprovider.hpp
 *
 * File created by : Corentin Gay
 * File was created at : 08/10/2017
 */

#pragma once


class Processor
{
};

class InterruptProvider
{
	public:
		// Check if there is an interrupt to run.
		bool hasInterrupt();

		// Execute current interrupt.
		// Returns the nu,ber if cycles it took.
		int doInterrupt();

		void setProcessor(Processor *p){_p = p;}
	private:
		Processor *_p;
};
