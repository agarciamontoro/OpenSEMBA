#ifndef  _GRID_H_
# define _GRID_H_

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "Box.h"
#include "base/class/ClassBase.h"

template<class T, Int D> class Box;

template<Int D>
class Grid : public virtual ClassBase {
    typedef Box<Real,D> BoxRD;
    typedef Box<Int ,D> BoxID;
    typedef CartesianVector<Real,D> CVecRD;
    typedef CartesianVector<Int,D> CVecID;
public:
    static const Real tolerance;

    Grid();
    Grid(const BoxRD&  boundingBox,
         const CVecRD& dxyz);
    Grid(const BoxRD&  boundingBox,
         const CVecID& dims);
    Grid(const CVecID& offset,
         const CVecRD& origin,
         const vector<Real> step[D]);
    Grid(const Grid& grid);
    ~Grid ();

    DEFINE_CLONE(Grid<D>);

    Grid& operator=(const Grid& cGrid);

    bool hasZeroSize() const;

    bool isInto(const CVecRD& pos) const;
    bool isInto(const Int dir, const Real pos) const;
    bool isRegular() const;
    bool isRegular(const Int d) const;
    bool isCartesian() const;
    bool isCell(const CVecRD& position,
            const Real tol = tolerance) const;
    bool isCell(const vector<CVecRD>& positions,
            const Real tol = tolerance) const;
    bool isCell(const CVecID& pos,
                const Real tol = tolerance) const { return true; }

    CVecID getNumCells() const;
    CVecID getOffset() const { return offsetGrid_; }
    CVecRD getOrigin() const { return origin_;     }

    vector<Real> getStep(const Int dir) const;
    Real getMinimumSpaceStep() const;

    BoxRD getFullDomainBoundingBox() const;
    BoxRD getBoundingBox(const BoxID& bound) const;
    BoxRD getBoxRContaining(const CVecRD& point) const;
    BoxID getBoxIContaining(const CVecRD& point) const;

    vector<CVecRD> getCenterOfCellsInside(const BoxRD& bound) const;
    vector<Real> getPosInRange(const Int dir,
                               const Real min,
                               const Real max) const;

    vector<CVecRD> getPos() const;
    vector<Real>   getPos(const Int dir) const;
    Real           getPos(const Int dir, const Int i) const;
    CVecRD         getPos(const CVecID& ijk) const;
    CVecRD         getPos(const CVecRD& ijk) const { return ijk; }

    pair<Int, Real>      getCellPair(const Int  dir,
                                     const Real x,
                                     const bool approx = true,
                                     const Real tol = tolerance,
                                     bool* err = NULL) const;
    pair<CVecID, CVecRD> getCellPair(const CVecRD& pos,
                                     const bool approx = true,
                                     const Real tol = tolerance,
                                     bool* err = NULL) const;
    Int    getCell(const Int   dir,
                   const Real  x,
                   const bool  approx = true,
                   const Real  tol = tolerance,
                   bool* err = NULL) const;
    CVecID getCell(const CVecRD& pos,
                   const bool  approx = true,
                   const Real  tol = tolerance,
                   bool* err = NULL) const;
    CVecID getCell(const CVecID& pos,
                   const bool  approx = true,
                   const Real  tol = tolerance) const { return pos; }

    void applyScalingFactor(const Real factor);
    void enlarge(const pair<CVecID,CVecID>& additionalCells,
                 const pair<CVecRD,CVecRD>& sizesOfNewCells);

    void printInfo() const;
private:

    CVecID offsetGrid_;
    CVecRD origin_;
    vector<Real> pos_[D];
};

typedef Grid<3> Grid3;

#endif //_cartesianGrid_hxx
