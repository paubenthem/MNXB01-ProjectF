#ifndef COVTRENDER_H
#define COVTRENDER_H

#include <string>
class tempTrender {
	public:
	explicit tempTrender(const std::string& file1Path, const std::string& file2Path); //Construct using the specified file
	~tempTrender() {} //Destructor

    void cov() const;
    void cov(int lag) const; //the lag is how many times we multiply the minimum time step

	private:
	
};
#endif
