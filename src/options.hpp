/*
 * Copyright © 2012 Felix Höfling
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <ostream>

/**
 * define, parse, and store command line options of the program
 */
class program_options : boost::noncopyable
{
public:
    program_options() {}

    /** parse and store command line options */
    void parse(int argc, char** argv);

    /** print option values */
    void print(std::ostream& ostr, std::string const& prefix = "");

    /** retrieve option value as specified type */
    template <typename T>
    T get(std::string const& name) const
    {
        if (!vm_.count(name)) {
            throw std::logic_error(std::string("missing option value: ") + name);
        }
        return vm_[name].as<T>();
    }

    /** retrieve option value as double by default */
    double get(std::string const& name) const
    {
        return get<double>(name);
    }

    /** check whether option value exists */
    bool has(std::string const& name) const
    {
        return vm_.count(name) > 0;
    }

private:
    /** store parsed program options */
    boost::program_options::variables_map vm_;
};

#endif /* ! OPTIONS_HPP */
