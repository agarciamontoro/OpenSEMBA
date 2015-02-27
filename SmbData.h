/*
 * SmbData.h
 *
 *  Created on: Mar 28, 2014
 *      Author: luis
 */

#ifndef SMBDATA_H_
#define SMBDATA_H_

#include "ProjectFile.h"
#include "inputs/GlobalProblemData.h"
#include "inputs/OutputRequestGroup.h"
#include "inputs/electromagneticSources/EMSourceGroup.h"
#include "inputs/physicalModel/PhysicalModelGroup.h"
#include "inputs/LayerGroup.h"
#include "inputs/MeshingParameters.h"

class SmbData : public ProjectFile {
public:
    GlobalProblemData* gData;
    LayerGroup* layers;
    PhysicalModelGroup* pMGroup;
    EMSourceGroup* emSources;
    OutputRequestGroup* outputRequests;
    MeshingParameters* meshingParams;
    MeshVolume* mesh;
    SmbData();
    virtual ~SmbData();
    virtual SmbData& operator=(const SmbData& rhs);
    void applyGeometricScalingFactor();
    void ignorePMLs();
    void detectAndAssignPMLRegions();
    virtual void printInfo() const;
};

#endif /* SMBDATA_H_ */
