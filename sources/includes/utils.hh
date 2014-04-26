#pragma once

#include <string>
#include <sstream>
#include <utility>

// doit être > 0 ; plus c'est grand plus la fonction est linéaire
const double LINE = 2.5;

double inv(double x);

template<typename T>
std::string typeToString(T x)
{
    std::ostringstream flux;
    flux << x;

    return flux.str();
}

template<class T>
class ValuePtr
{
    public:
        ValuePtr() : m_nptr(NULL) {} // Initialisation a NULL
        ValuePtr(T *nptr) : m_nptr(nptr) {} // Initialisation a nptr
        // Nous manipulons une collection polymorphique donc le constructeur par copie est
        // obligé d'appeler une méthode de clonage de l'objet pointé. Note : l'opérateur ->
        // permet bien d'accéder a m_nptr.clone();
        ValuePtr(const ValuePtr &other) : m_nptr(other->clone()) {}
        ~ValuePtr() { delete m_nptr; }

        // Surcharge opérateur '->'. L'opérateur agit de cette façon : ValuePtr->méthode de T
        // car il fonctionne de cette manière : (instance de ValuePtr.operator->())->méthode
        // et il respecte l'encapsulation
        T* operator->() const { return m_nptr; }
        ValuePtr& operator=(const ValuePtr &other) // Surcharge opérateur =
        {
            ValuePtr<T> temp(other); // Se désallou en fin de portée
            // Echange les deux valeurs (c'est le *nptr de this qui est désalloué car le
            // swap s'éffectue avant la fin de la portée)
            std::swap(m_nptr, temp.m_nptr);

            return *this;
        }

    private:
        T *m_nptr;
};
