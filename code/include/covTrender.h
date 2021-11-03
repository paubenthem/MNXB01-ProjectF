#ifndef COVTRENDER_H
#define COVTRENDER_H

#include <string>
#include <vector>


class covTrender {
	public:
	explicit covTrender(const std::string& file1Path, const std::string& file2Path); //Construct using the specified file
	~covTrender() {} //Destructor

    void cov() const;
    void cov(int lag) const; //the lag is in minuets

	private:
        

	
};
#endif
