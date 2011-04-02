/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                   http://mrpt.sourceforge.net/                            |
   |                                                                           |
   |   Copyright (C) 2005-2011  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */

#include <mrpt/gui.h>
#include <mrpt/utils.h>

using namespace mrpt;
using namespace mrpt::gui;
using namespace mrpt::math;
using namespace mrpt::utils;
using namespace std;

#include <mrpt/examples_config.h>
string   myDataDir( MRPT_EXAMPLES_BASE_DIRECTORY + string("imageBasics/") );

// ------------------------------------------------------
//				TestImageCap
// ------------------------------------------------------
void TestImageConversion()
{
	// BMP -> JPEG conversion tester:
	// --------------------------------
	CImage		img,img2;
	CTicTac			tictac;

	tictac.Tic();
	if (!img.loadFromFile(myDataDir+string("frame_color.jpg")))
	{
		cerr << "Cannot load " << myDataDir+string("frame_color.jpg") << endl;
		return;
	}
	printf("Image loaded in %.03fms\n", 1000*tictac.Tac() );

	if (false)   // A very simple test:
	{
		CDisplayWindow		win1("JPEG file, color");
		win1.setPos(10,10);

		win1.showImage( img );

		cout << "Push a key in the console or in the window to continue...";
		win1.waitForKey();
		cout << "Done" << endl;

		img = img.grayscale();

		CDisplayWindow		win2("JPEG file, gray");
		win2.showImage( img );
		win1.setPos(300,10);

		cout << "Push a key in the console or in the window to continue...";
		win2.waitForKey();
		cout << "Done" << endl;

		mrpt::system::pause();
		return;
	}

	CDisplayWindow		win1("win1"),win2("win2"),win3("win3");

	CImage			imgSmall( img );
	CImage			imgGray( imgSmall.grayscale() );
	CImage			imgSmall2( imgGray.scaleHalfSmooth() );

	// Test some draw capabilities:
	// ---------------------------------
	imgSmall.rectangle( 85,35, 170,170,TColor(255,0,0),10);

	imgSmall.line( 550,75, 650,25,TColor(0,0,255));
	imgSmall.line( -10,-20, 20,30,TColor(0,0,255));

	CMatrix 	COV(2,2);
	COV(0,0) = 100;
	COV(1,1) = 50;
	COV(0,1) = COV(1,0) = -30;
	imgSmall.ellipseGaussian( &COV, 600.0f,50.0f, 2, TColor(255,255,0), 4);
	imgGray.ellipseGaussian( &COV, 100.0f,100.0f, 2, TColor(0,0,255), 4);

	imgSmall.drawImage( 400,500,imgGray );

	// Show the windows now:
	// ------------------------------------------------------
	win1.showImage( imgSmall ); win1.setPos(0,0);
	win2.showImage( imgSmall2 ); win2.setPos(810,0);
	win3.showImage( imgGray ); win3.setPos(810,400);

	cout << "Press any key on 'win3' to exit" << endl;
	win3.waitForKey();

	tictac.Tic();
	img2.saveToFile("frame_out.jpg");
	printf("jpeg file saved in %.03fms\n", 1000.0f*tictac.Tac() );

	imgSmall2.saveToFile("frame_out_small.png");

	return;
}

// ------------------------------------------------------
//						MAIN
// ------------------------------------------------------
int main()
{
	try
	{
		TestImageConversion();
		return 0;
	} catch (std::exception &e)
	{
		std::cout << "MRPT exception caught: " << e.what() << std::endl;
		return -1;
	}
	catch (...)
	{
		printf("Untyped exception!!");
		return -1;
	}
}
