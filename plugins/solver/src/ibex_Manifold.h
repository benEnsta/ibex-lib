//============================================================================
//                                  I B E X
// File        : ibex_Manifold.h
// Author      : Gilles Chabert
// Copyright   : IMT Atlantique (France)
// License     : See the LICENSE file
// Created     : Oct 01, 2017
//============================================================================

#ifndef __IBEX_MANIFOLD_H__
#define __IBEX_MANIFOLD_H__

#include "ibex_IntervalVector.h"
#include "ibex_Solver.h"

#include <fstream>
#include <vector>
#include <stdint.h>

namespace ibex {

/**
 * \ingroup strategy
 *
 * \brief Representation of a manifold with boxes.
 *
 * Contrary to a paving, boxes may overlap in a "manifold"
 * (more than just on their boundaries).
 */
class Manifold {
public:

	Manifold(int n, int m, int nb_ineq);

	/**
	 * Delete this.
	 */
	virtual ~Manifold();

	/**
	 * \brief Load a manifold from a file.
	 */
	void load(const char* filename);

	/**
	 * \brief Write the manifold into a file.
	 */
	void write(const char* filename) const;

	/**
	 * \brief Write the manifold into a file (in text format)
	 *
	 * See #format().
	 */
	void write_txt(const char* filename) const;

	/**
	 * \brief Clear all.
	 */
	void clear();

	/**
	 * \brief Total number of boxes
	 *
	 * size = #inner + #boundary + #unknown + #pending
	 */
	int size() const;

	/**
	 * \brief Return the format of the report.
	 */
	static std::string format();

	//Status status() const;

	/**
	 * \brief Number of variables
	 */
	unsigned int n;

	/**
	 * \brief Number of equalities.
	 */
	unsigned int m;

	/**
	 * \brief Number of inequalities.
	 */
	unsigned int nb_ineq;

	/*
	 * \brief Return status of the last solving.
	 */
	Solver::Status status;

	/*
	 * \brief Inner boxes
	 */
	std::vector<SolverOutputBox> inner;

	/*
	 * \brief Boundary boxes
	 */
	std::vector<SolverOutputBox> boundary;

	/*
	 * \brief Boundary boxes
	 */
	std::vector<SolverOutputBox> unknown;

	/*
	 * \brief Pending boxes
	 */
	std::vector<SolverOutputBox> pending;

	/*
	 * \brief CPU running time used to obtain this manifold.
	 */
	double time;

	/**
	 * \brief Number of cells used to obtain this manifold.
	 */
	unsigned int nb_cells;

	/**
	 * \brief Manifold file format version.
	 */
	static const int FORMAT_VERSION;

protected:

	static const int  SIGNATURE_LENGTH;
	static const char* SIGNATURE;

	unsigned int read_int(std::ifstream& f);
	double read_double(std::ifstream& f);
	void read_signature(std::ifstream& f);
	SolverOutputBox read_output_box(std::ifstream& f);

	void write_int(std::ofstream& f, uint32_t x) const;
	void write_double(std::ofstream& f, double x) const;
	void write_signature(std::ofstream& f) const;
	void write_output_box(std::ofstream& f, const SolverOutputBox& sol) const;
	void write_output_box_txt(std::ofstream& file, const SolverOutputBox& sol) const;
};

std::ostream& operator<<(std::ostream& os, const Manifold& manif);

/*============================================ inline implementation ============================================ */

inline const Manifold& Solver::get_manifold() const { return *manif; }

inline double Solver::get_time() const { return time; }

inline double Solver::get_nb_cells() const { return nb_cells; }

inline int Manifold::size() const {
	return inner.size() + boundary.size() + unknown.size() + pending.size();
}


} /* namespace ibex */

#endif /* __IBEX_MANIFOLD_H__ */
