#ifndef _MYVECTOR_
#define _MYVECTOR_

using namespace std;

/**
 * \brief Indicates classes constructed by Vitor Greati.
 * */
namespace Greati {
	

	template<typename T>
	/**
	 *  \brief A simple ArrayList implementation.
	 * 
	 * \details ArrayList with a few methods, useful for
	 * BARES project mainly.
	 *
	 * @author Vitor Greati
	 * @version 1.1
	 * */
	class Vector {
		
		
		private:
			static const int DEFAULT_CAP = 50; /**< The default capacity of the list.*/
			
			T* vecData; 			   /**< Pointer to the data.*/ 
			int vecSize;			   /**< Logical size of the list.*/
			int vecCapacity;		   /**< Size of the list in memory. */
			
			/** \brief Doubles the capacity and keep the data.
			 * */	
			void doubleData(); 
			
			public:
				
			/** 
			 * \brief Constructor: takes the size.
			 * \details As parameter is optional, it can be considered
			 * the default constructor.
			 * */
			Vector(int _cap = DEFAULT_CAP) : vecCapacity {_cap}, vecSize{0} {
				if (_cap <= 0)
					throw std::invalid_argument("Vector:Vector(int, const T&) : Invalid size.");	
				else vecData = new T[_cap];
			};
			
			 /**
			 * \brief Destructor method.
			 * */
			~Vector(void);

			/** 
			 * \brief Returns the logical size of the list.
			 * */
			int size(void) const;

			/**
			 * \brief Fill vector with a value.
			 * */
			void fill(const T&);

			/**
			 * \brief Add an element to the end.
			 * */
			void push_back(const T &);

			/** 
			 * \brief AssigAt operador
			 */
			T& operator[](int);
			
			/**
			 * \brief At operator.
			 * */
			const T operator[](int) const;
			
			/**
			 * \brief Equals operator.
			 * */
			bool operator==(const Vector &) const;
		        
			/**
			 * \brief Assign operator.
			 * */
			const Vector& operator=(const Vector &);	
			
			/**
			 * \brief Assign list operator.
			 * */
			const Vector& operator=(const initializer_list<T> &);
	};
}
#include "../src/vector.cpp"
#endif
