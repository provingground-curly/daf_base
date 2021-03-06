#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "lsst/daf/base/Citizen.h"

namespace py = pybind11;

namespace lsst {
namespace daf {
namespace base {

PYBIND11_MODULE(citizen, mod) {
    py::class_<Citizen, std::shared_ptr<Citizen>> cls(mod, "Citizen");

    cls.def("repr", &Citizen::repr);
    cls.def("markPersistent", &Citizen::markPersistent);
    cls.def_static("census", (int (*)(int, Citizen::memId)) & Citizen::census);
    cls.def_static("census", (const std::vector<const Citizen *> *(*)()) & Citizen::census,
                   py::return_value_policy::reference);
    /* It is strange to expose cout to Python, so instead make a new wrapper */
    cls.def_static("census", [](Citizen::memId id) { Citizen::census(std::cout, id); });
    // TODO: pybind11 can't handle an owning pointer to a container of non-owning pointers
    // ::reference is a temporary workaround until we figure out a better way
    cls.def_static("census", (std::vector<Citizen const *> const *(*)()) & Citizen::census,
                   py::return_value_policy::reference);
    cls.def("getId", &Citizen::getId);
    cls.def("markPersistent", &Citizen::markPersistent);
    cls.def_static("getNextMemId", &Citizen::getNextMemId);
    cls.def_static("setNewCallbackId", &Citizen::setNewCallbackId);
    cls.def_static("setDeleteCallbackId", &Citizen::setDeleteCallbackId);
}

}  // base
}  // daf
}  // lsst
