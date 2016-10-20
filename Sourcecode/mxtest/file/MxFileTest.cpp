// MusicXML Class Library v0.3.0
// Copyright (c) 2015 - 2016 by Matthew James Briggs

#include "mxtest/file/MxFileTest.h"
#include "cpul/cpulFailure.h"
#include "cpul/cpulTestResult.h"

#include <sstream>

namespace mxtest
{
    MxFileTest::MxFileTest( mxtest::TestFile inTestFile, std::string inTestName, std::string inTestCppFileName, int inTestCppFileLineNumber )
    : ::Test{ inTestName, inTestCppFileName, inTestCppFileLineNumber }
    , myTestFile{ inTestFile }
    , myTestName{ inTestName }
    , myCppFileName{ inTestCppFileName }
    , myCppFileLineNumber{ inTestCppFileLineNumber }
    , myIsSuccess{ false }
    , myFailureMessage{}
    {
        
    }
    
    
    void MxFileTest::runTest( TestResult& testResult )
    {
        bool isExceptionThrown = false;
        std::string exceptionMessage;
        
        try
        {
            this->runTestCode();
        }
        catch ( std::exception& e )
        {
            isExceptionThrown = true;
            exceptionMessage = std::string{ e.what() };
        }
        catch ( ... )
        {
            isExceptionThrown = true;
            exceptionMessage = "exception of unknown (non-standard) type";
        }
        
        if( isExceptionThrown )
        {
            std::stringstream failureMessage;
            failureMessage << "'" << myTestName << " "  << testFileName() << " exception was thrown '" << exceptionMessage << "'";
            
            ::Failure exceptionFailure
            {
                failureMessage.str(), // std::string theCondition
                myCppFileName,        // std::string theFileName
                myCppFileLineNumber   // long theLineNumber
            };
            testResult.addFailure( exceptionFailure );
        }
        else if( !getIsSuccess() )
        {
            std::stringstream failureMessage;
            failureMessage << "'" << myTestName << "' "  << testFileName() << " '" << getFailureMessage() << "'";
            
            ::Failure testFailure
            {
                failureMessage.str(), // std::string theCondition
                myCppFileName,        // std::string theFileName
                myCppFileLineNumber   // long theLineNumber
            };
            testResult.addFailure( testFailure );
        }
    }
    
    const std::string& MxFileTest::testFileName() const
    {
        return myTestFile.fileName;
    }
    
    
    const std::string MxFileTest::testFileNamePart() const
    {
        return myTestFile.getFileNamePart();
    }
    
    
    const std::string MxFileTest::testFileExtension() const
    {
        return myTestFile.fileName.substr( myTestFile.fileName.size() - 3, 3 );
    }
    
    
    const std::string& MxFileTest::testFilePath() const
    {
        return myTestFile.path;
    }
    
    
    const std::string& MxFileTest::testSubdirectory() const
    {
        return myTestFile.subdirectory;
    }
    
    
    bool MxFileTest::getIsSuccess() const
    {
        return myIsSuccess;
    }
    
    
    void MxFileTest::setIsSuccess( bool inIsSuccess )
    {
        myIsSuccess = inIsSuccess;
    }
    
    
    const std::string& MxFileTest::getFailureMessage() const
    {
        return myFailureMessage;
    }
    
    
    void MxFileTest::setFailureMessage( std::string inMessage )
    {
        myFailureMessage = inMessage;
    }


    // MxFileTest::MxFileTest( MxFileTest&& other )
    // : Test{ std::move( other ) }
    // , myTestFile{ std::move( other.myTestFile ) }
    // , myTestName{ std::move( other.myTestName ) }
    // , myCppFileName{ std::move( other.myCppFileName ) }
    // , myCppFileLineNumber{ std::move( other.myCppFileLineNumber ) }
    // , myIsSuccess{ std::move( other.myIsSuccess ) }
    // , myFailureMessage{ std::move( other.myFailureMessage ) }
    // {

    // }


    // MxFileTest::MxFileTest( const MxFileTest& other )
    // : Test{ other }
    // , myTestFile{ other.myTestFile }
    // , myTestName{ other.myTestName }
    // , myCppFileName{ other.myCppFileName }
    // , myCppFileLineNumber{ other.myCppFileLineNumber }
    // , myIsSuccess{ other.myIsSuccess }
    // , myFailureMessage{ other.myFailureMessage } 
    // {

    // }


    // MxFileTest& MxFileTest::operator=( MxFileTest&& other )
    // {
    //     return *this;
    // }


    // MxFileTest& MxFileTest::operator=( const MxFileTest& other )
    // {
    //     return *this;
    // }
}
