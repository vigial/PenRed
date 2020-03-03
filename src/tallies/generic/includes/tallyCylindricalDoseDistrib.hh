
//
//
//    Copyright (C) 2019 Universitat de València - UV
//    Copyright (C) 2019 Universitat Politècnica de València - UPV
//
//    This file is part of PenRed: Parallel Engine for Radiation Energy Deposition.
//
//    PenRed is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    PenRed is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with PenRed.  If not, see <https://www.gnu.org/licenses/>. 
//
//    contact emails:
//
//        vicent.gimenez.alventosa@gmail.com
//        vicente.gimenez@uv.es
//    
//

 
#ifndef __PEN_CYLINDRICAL_DOSE_DISTRIB_TALLY__
#define __PEN_CYLINDRICAL_DOSE_DISTRIB_TALLY__


#include "pen_constants.hh"

class pen_CylindricalDoseDistrib: public pen_genericTally<pen_particleState> {
    DECLARE_TALLY(pen_CylindricalDoseDistrib,pen_particleState)
    
private:

  bool prtxyz;
  int nr,nz;
  int rnbin;
  static const int nbinmax=100000;
  double edptmp[nbinmax];
  double edep[nbinmax];
  double edep2[nbinmax];
  double idens[nbinmax];
  double nlast[nbinmax];
  double dr,dz,idr,idz;
  double rmin,zmin,r2min,r2max; 

    
public:
    
  pen_CylindricalDoseDistrib() : pen_genericTally( USE_LOCALEDEP |
						   USE_BEGINPART |
						   USE_BEGINHIST |
						   USE_STEP |
						   USE_ENDSIM |
						   USE_MOVE2GEO),
				 nr(0),
				 nz(0),
				 rnbin(0)
				 
  {}
  
  void updateEdepCounters(const double dE,
                          const double nhist,
                          const double X,
			  const double Y,
			  const double Z,
			  const double WGHT);
 
  
  void tally_localEdep(const double nhist,
		       const pen_KPAR /*kpar*/,
		       const pen_particleState& state,
		       const double dE);
  
  void tally_beginPart(const double nhist,
		       const unsigned /*kdet*/,
		       const pen_KPAR /*kpar*/,
		       const pen_particleState& state);
  
  void tally_beginHist(const double nhist,
		       const unsigned /*kdet*/,
		       const pen_KPAR /*kpar*/,
		       const pen_particleState& state);

  void tally_step(const double nhist,
		  const pen_KPAR /*kpar*/,
		  const pen_particleState& state,
		  const tally_StepData& stepData);
  
  void tally_move2geo(const double nhist,
		      const unsigned /*kdet*/,
		      const pen_KPAR /*kpar*/,
		      const pen_particleState& state,
		      const double /*dsef*/,
		      const double /*dstot*/);
  
  
  void tally_endSim(const double /*nhist*/);
    
  int configure(const wrapper_geometry& geometry,
		const abc_material* const materials[constants::MAXMAT],
		const pen_parserSection& config,
		const unsigned verbose);
  void flush();
  void saveData(const double nhist) const;
  int sumTally(const pen_CylindricalDoseDistrib& tally);
};


#endif