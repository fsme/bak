//@(#) Buffer for ::read(2) and ::write(2) with report
// Licence: GPLv3 BSD
// Author Andrew Wingorodov <http://andr.mobi/>
//$Id$

#ifndef CXX_BUFFER_HPP
#define CXX_BUFFER_HPP 1

#include <fcntl.h>

#include <iostream>

#include <logostream.hpp>

using namespace std;
using namespace cxx;

namespace cxx {

///\class buffer
///\brief Virtual Buffer for ::read(2) or ::write(2) with report 

class buffer
{
public:
///\brief Create
buffer ()
	: _size (0)
	, _ptr (0)
	, _is_open (false)
{}

///\brief Destroy
virtual ~buffer () { this->close (); }

///\brief Open buffer
virtual void open (
	const std::string& path_ ///\param path_ File name
) = 0;

///\brief Close buffer
void close ()
{
	if ( is_open())
		{ ::close (_fd); _is_open = false; }

	if ( _ptr != 0)
			{ delete [] _ptr; _ptr = 0; }

	_is_open = false;
}

///\brief Get buffered data size
ssize_t size () const { return _size; }

///\brief Is open
bool is_open () const { return _is_open; }

///\brief Get void pointer
///\return Pointer to void 
operator void* () const { return (void*)_ptr; }


///\brief Virtual read
virtual bool read () = 0;

///\brief Virtual write
virtual bool write (void* ptr_, ssize_t size_) = 0;

protected:
	ssize_t		_size;		///< Buffered data size (amount read or write)
	int			_fd;		///< File descriptor
	uint8_t*	_ptr;		///< Buffer pointer
	bool		_is_open;	///< Is open flag


///\brief Show progress
void report () const
{
static ssize_t _total = 0;
	if (env::iron.exists ("q")) ///< Quiet mode
		return;

	_total += _size;
	cout.put (015);
	cout.flush();
	cout << _total << " bytes are processed " << flush;
}

}; //class buffer



///\class ibuffer
///\brief Input buffer to ::read(2)

class ibuffer
	: public buffer
{
public:

///\brief Create
explicit ibuffer (
 	 const std::string& path_ ///\param path_ Path to file
	, ssize_t size_ = 512 ///\param size_ Size of memory buffer
)
	: buffer ()
	, _maxsize (size_)
{
	open (path_);
}

///\brief Destroy
virtual ~ibuffer () {}

///\brief Open buffer
virtual void open (
	const std::string& path_ ///\param path_ File name
) {
	if (is_open()) return;

	_fd =::open ( path_.c_str(), O_RDONLY, 0); 
	if (_fd == -1)
		throw er::no ( path_+ " open error: ");

	allocate (_maxsize);
	_is_open = true;
}

///\brief Set buffer size (allocate memory)
void allocate (
	const ssize_t size_ ///\param size_ New size for buffer
) {
	_maxsize = size_;
	if (0 != _ptr)  delete [] _ptr;
	_ptr = new uint8_t [_maxsize];
}

///\brief Read from file
///\return False if read (2) return 0
virtual bool read ()
{
	_size = ::read (_fd, _ptr, _maxsize);
	if (_size == -1)
		throw er::no ("read(2) error: ");

	if (_size) {
	///	report ();
		return true;
	}
	else
		return false;
}

///\brief Empty write
///\return False always
virtual bool write (
	  void* ptr_ = 0	///\param ptr_ Buffer pointer
	, ssize_t size_ = 0	///\param size_ Size to write
) {
	return false;
}

protected:
	ssize_t		_maxsize;	///< Buffer size

}; //class ibuffer


///\class obuffer
///\brief Output buffer to ::write(2)

class obuffer
	: public buffer
{
public:

///\brief Create
explicit obuffer (
 	  const std::string& path_ ///\param path_ Path to file
)
	: buffer () 
{
	open (path_);
}

///\brief Destroy
virtual ~obuffer ()
{
	if ( !env::iron.exists ("q")) cout << endl; ///< Close report show
}

///\brief Open buffer
virtual void open (
	const std::string& path_ ///\param path_ File name
) {
	if (is_open()) return;

	_fd =::open ( path_.c_str(), O_WRONLY | O_CREAT | O_TRUNC); 
	if (_fd == -1)
		throw er::no ( path_+ " open to write error: ");

	_is_open = true;
}

///\brief Write to file
///\return True if ::write(2) return more then zero
virtual bool write (
	  void* ptr_	///\param ptr_ Buffer pointer
	, ssize_t size_	///\param size_ Size to write
) {
	_size = ::write (_fd, ptr_, size_);
	if (_size == -1)
		throw er::no ("write(2) error: ");

	if (_size) {
		report ();
		return true;
	}
	else
		return false;
}

///\brief Empty read
///\return False always
virtual bool read () { return false; }

}; //class ibuffer


} //::cxx

#endif ///CXX_BUFFER_HPP
