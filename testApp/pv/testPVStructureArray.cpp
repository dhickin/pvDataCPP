/* testPVStructureArray.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/* Author:  Marty Kraimer Date: 2010.10 */

#include <cstddef>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <cstdio>

#include <epicsAssert.h>
#include <epicsExit.h>

#include <pv/requester.h>
#include <pv/pvIntrospect.h>
#include <pv/pvData.h>
#include <pv/convert.h>
#include <pv/standardField.h>
#include <pv/standardPVField.h>

#include <epicsUnitTest.h>
#include <testMain.h>

using namespace epics::pvData;

static FieldCreatePtr fieldCreate;
static PVDataCreatePtr pvDataCreate;
static StandardFieldPtr standardField;
static StandardPVFieldPtr standardPVField;
static ConvertPtr convert;

static void testBasic()
{
    testDiag("Basic structure array ops");

    StructureArrayConstPtr alarmtype(
        fieldCreate->createStructureArray(standardField->alarm()));

    PVStructureArrayPtr alarmarr(pvDataCreate->createPVStructureArray(alarmtype));

    testOk1(alarmarr->getLength()==0);

    alarmarr->setLength(5);

    testOk1(alarmarr->getLength()==5);

    PVStructureArray::const_svector aview = alarmarr->view();

    testOk1(aview.size()==5);
    testOk1(aview[4].get()==NULL);

    alarmarr->append(2);

    testOk1(alarmarr->getLength()==7);

    aview = alarmarr->view();

    testOk1(aview[4].get()==NULL);
    testOk1(aview[5].get()!=NULL);
    testOk1(aview[6].get()!=NULL);
}

static void testCompress()
{
    testDiag("Test structure array compress");

    StructureArrayConstPtr alarmtype(
        fieldCreate->createStructureArray(standardField->alarm()));

    PVStructureArrayPtr alarmarr(pvDataCreate->createPVStructureArray(alarmtype));

    alarmarr->setLength(5);

    testOk1(alarmarr->getLength()==5);

    alarmarr->compress();

    testOk1(alarmarr->getLength()==0);

    alarmarr->setLength(4);

    testOk1(alarmarr->getLength()==4);

    PVStructureArray::svector contents(10);

    contents[2] = pvDataCreate->createPVStructure(standardField->alarm());
    contents[4] = pvDataCreate->createPVStructure(standardField->alarm());
    contents[5] = pvDataCreate->createPVStructure(standardField->alarm());
    contents[8] = pvDataCreate->createPVStructure(standardField->alarm());

    alarmarr->replace(contents);

    testOk1(!contents.unique());
    testOk1(alarmarr->getLength()==10);

    alarmarr->compress();

    testOk1(contents.unique()); // a realloc happened
    testOk1(alarmarr->getLength()==4);

    PVStructureArray::svector compressed(alarmarr->reuse());

    testOk1(contents[2]==compressed[0]);
    testOk1(contents[4]==compressed[1]);
    testOk1(contents[5]==compressed[2]);
    testOk1(contents[8]==compressed[3]);
}

static void testRemove()
{
    testDiag("Test structure array remove");
    
    PVStructureArray::svector contents(10);
    
    for(size_t i=0; i<contents.size(); i++)
        contents[i] = pvDataCreate->createPVStructure(standardField->alarm());

    StructureArrayConstPtr alarmtype(
        fieldCreate->createStructureArray(standardField->alarm()));
    PVStructureArrayPtr alarmarr(pvDataCreate->createPVStructureArray(alarmtype));

    alarmarr->replace(contents);

    alarmarr->remove(0, 10); // all

    testOk1(alarmarr->getLength()==0);

    alarmarr->replace(contents);

    alarmarr->remove(1, 1);

    PVStructureArray::const_svector check(alarmarr->view());

    testOk1(contents[0]==check[0]);
    testOk1(contents[2]==check[1]);
    testOk1(contents[3]==check[2]);
}

MAIN(testPVStructureArray)
{
    testPlan(0);
    testDiag("Testing structure array handling");
    fieldCreate = getFieldCreate();
    pvDataCreate = getPVDataCreate();
    standardField = getStandardField();
    standardPVField = getStandardPVField();
    testBasic();
    testCompress();
    testRemove();
    return testDone();
}
