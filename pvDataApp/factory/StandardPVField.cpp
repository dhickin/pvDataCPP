/* StandardPVField.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvDataCPP is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
#include <string>
#include <stdexcept>
#include <lock.h>
#include "pvIntrospect.h"
#include "pvData.h"
#include "convert.h"
#include "standardField.h"
#include "standardPVField.h"

namespace epics { namespace pvData { 

static String notImplemented("not implemented");
static FieldCreate* fieldCreate = 0;
static PVDataCreate* pvDataCreate = 0;
static StandardField *standardField = 0;
static StandardPVField *standardPVField = 0;

StandardPVField::StandardPVField(){}

StandardPVField::~StandardPVField(){}


PVScalar * StandardPVField::scalar(PVStructure *parent,
    String fieldName,ScalarType type)
{
    ScalarConstPtr field = standardField->scalar(fieldName,type);
    return pvDataCreate->createPVScalar(parent,field);
}

PVStructure * StandardPVField::scalar(PVStructure *parent,
    String fieldName,ScalarType type,String properties)
{
    StructureConstPtr field = standardField->scalar(fieldName,type,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVScalarArray * StandardPVField::scalarArray(PVStructure *parent,
    String fieldName,ScalarType elementType)
{
    ScalarArrayConstPtr field = standardField->scalarArray(
        fieldName,elementType);
    return pvDataCreate->createPVScalarArray(parent,field);
}

PVStructure * StandardPVField::scalarArray(PVStructure *parent,
    String fieldName,ScalarType elementType, String properties)
{
    StructureConstPtr field = standardField->scalarArray(
        fieldName,elementType,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructureArray * StandardPVField::structureArray(PVStructure *parent,
    String fieldName,StructureConstPtr structure)
{
    StructureArrayConstPtr field = standardField->structureArray(
        fieldName,structure);
    return pvDataCreate->createPVStructureArray(parent,field);
}

PVStructure* StandardPVField::structureArray(PVStructure *parent,
    String fieldName,StructureConstPtr structure,String properties)
{
    StructureConstPtr field = standardField->structureArray(
        fieldName,structure,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::enumerated(PVStructure *parent,
    String fieldName,StringArray choices)
{
    StructureConstPtr field = standardField->enumerated(
        fieldName,choices);
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::enumerated(PVStructure *parent,
    String fieldName,StringArray choices, String properties)
{
    StructureConstPtr field = standardField->enumerated(
        fieldName,choices,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVScalar * StandardPVField::scalarValue(PVStructure *parent,
    ScalarType scalarType)
{
    ScalarConstPtr field = standardField->scalarValue(scalarType);
    return pvDataCreate->createPVScalar(parent,field);
}

PVStructure * StandardPVField::scalarValue(PVStructure *parent,
    ScalarType type,String properties)
{
    StructureConstPtr field = standardField->scalarValue(type,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVScalarArray * StandardPVField::scalarArrayValue(PVStructure *parent,
    ScalarType elementType)
{
    ScalarArrayConstPtr scalarArray =
        standardField->scalarArrayValue(elementType);
    return pvDataCreate->createPVScalarArray(0,scalarArray);
}

PVStructure * StandardPVField::scalarArrayValue(PVStructure *parent,
    ScalarType elementType, String properties)
{
    StructureConstPtr field = standardField->scalarArrayValue(
        elementType,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructureArray * StandardPVField::structureArrayValue(PVStructure *parent,
    StructureConstPtr structure)
{
    StructureArrayConstPtr field = standardField->structureArrayValue(
        structure);
    return pvDataCreate->createPVStructureArray(parent,field);
}

PVStructure * StandardPVField::structureArrayValue(PVStructure *parent,
    StructureConstPtr structure,String properties)
{
    StructureConstPtr field = standardField->structureArrayValue(
        structure,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::enumeratedValue(PVStructure *parent,
    StringArray choices)
{
    StructureConstPtr field = standardField->enumeratedValue( choices);
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::enumeratedValue(PVStructure *parent,
    StringArray choices, String properties)
{
    StructureConstPtr field = standardField->enumeratedValue(
        choices,properties);
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::alarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->alarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::timeStamp(PVStructure *parent)
{
    StructureConstPtr field = standardField->timeStamp();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::display(PVStructure *parent)
{
    StructureConstPtr field = standardField->display();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::control(PVStructure *parent)
{
    StructureConstPtr field = standardField->control();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::booleanAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->booleanAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::byteAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->byteAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::shortAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->shortAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::intAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->intAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::longAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->longAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::floatAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->floatAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::doubleAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->doubleAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::enumeratedAlarm(PVStructure *parent)
{
    StructureConstPtr field = standardField->enumeratedAlarm();
    return pvDataCreate->createPVStructure(parent,field);
}

PVStructure * StandardPVField::powerSupply(PVStructure *parent)
{
    StructureConstPtr alarmField = standardField->alarm();
    StructureConstPtr timeStampField = standardField->timeStamp();
    StructureConstPtr voltageField = standardField->scalar(
        String("voltage"),pvDouble,String("alarm"));
    StructureConstPtr powerField = standardField->scalar(
        String("power"),pvDouble,String("alarm"));
    StructureConstPtr currentField = standardField->scalar(
        String("current"),pvDouble,String("alarm"));
    FieldConstPtr fields[3];
    fields[0] = voltageField;
    fields[1] = powerField;
    fields[2] = currentField;
    StructureConstPtr valueField = standardField->structureValue( 3,fields);
    fields[0] = alarmField;
    fields[1] = timeStampField;
    fields[2] = valueField;
    StructureConstPtr structureField = standardField->structureValue(3,fields);
    return pvDataCreate->createPVStructure(parent,structureField);
}





class StandardPVFieldExt : public StandardPVField {
public:
    StandardPVFieldExt(): StandardPVField(){};
};

StandardPVField * getStandardPVField() {
    static Mutex mutex = Mutex();
    Lock xx(&mutex);

    if(standardPVField==0) {
        fieldCreate = getFieldCreate();
        pvDataCreate = getPVDataCreate();
        standardField = getStandardField();
        standardPVField = new StandardPVFieldExt();
    }
    return standardPVField;
}

}}