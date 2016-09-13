// CS 225 Lab02 Unit Tests

#include "png.h"
#include "util.h"
#include "proxy.h"

#include "image.h"
#include "image.h" // Deliberately check for double inclusion guards

using namespace util;

#if MP_PART(1)

UNIT_TEST(test_invertcolors, 4, 1, 5000)
{
	Image* myImage = new Image();
	myImage->readFromFile("in_01.png");
	myImage->invertcolors();

	ASSERT(*myImage == PNG("soln_inverted.png"));
	delete myImage;
	PASS;
}

UNIT_TEST(test_flipleft, 3, 1, 5000)
{
	Image* myImage = new Image();
	myImage->readFromFile("in_01.png");
	myImage->invertcolors();
	myImage->flipleft();
	
	ASSERT(*myImage == PNG("soln_flipped.png"));
	delete myImage;
	PASS;
}

UNIT_TEST(test_adjustbrightness, 3, 1, 5000)
{
	Image* myImage = new Image();
	myImage->readFromFile("in_01.png");
	myImage->invertcolors();
	myImage->flipleft();
	myImage->adjustbrightness(20, 20, -40);

	ASSERT(*myImage == PNG("soln_brightened.png"));
	delete myImage;
	PASS;
}

#endif // MP_PART(1)

#if MP_PART(2)

#include "scene.h"
#include "scene.h" // Deliberately check for double inclusion guards

UNIT_TEST(test_drawscene, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	Image result = set->drawscene();
	ASSERT(result == PNG("soln_scene.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_changelayer, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);

	set->changelayer(1, 3);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene2.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_translate, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);

	set->translate(0, 50, 50);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene3.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_getpicture, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();

	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene4.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_deletepicture, 0, 1, 5000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();
	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	
	set->deletepicture(3);
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene5.png"));
	delete set;
	PASS;
}

UNIT_TEST(test_cctor, 0, 1, 10000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();
	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	set->deletepicture(3);
	
	Scene* sc = new Scene(*set);
	sc->getpicture(0)->flipleft();
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene6.png")); // scene 5 and 6 should be the same
	result = sc->drawscene();
	ASSERT(result == PNG("soln_scene7.png"));
	delete set;
	delete sc;
	PASS;
}

UNIT_TEST(test_operator_equals, 0, 1, 10000)
{
	Scene* set = new Scene(5);
	Image result;
	set->addpicture("in_01.png", 0, 0, 0);
	set->addpicture("in_02.png", 1, 60, 60);
	set->addpicture("in_03.png", 2, 150, 0);
	set->changelayer(1, 3);
	set->translate(0, 50, 50);
	result = set->drawscene();
	set->getpicture(0)->adjustbrightness(-70,-70,-70);
	set->deletepicture(3);
	Scene* sc = new Scene(*set);
	sc->getpicture(0)->flipleft();

	delete set;
	set = new Scene(5);
	*set = *sc;
	result = set->drawscene();
	ASSERT(result == PNG("soln_scene8.png")); // scene 7 and 8 should be the same
	delete set;
	delete sc;
	PASS;
}

#endif
