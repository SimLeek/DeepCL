// Copyright Hugh Perkins 2015 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>

#include "util/FileHelper.h"
#include "util/StatefulTimer.h"
#include "loaders/ManifestLoaderv1.h"
#include "loaders/Loader.h"
#include "loaders/GenericLoaderv1Wrapper.h"

#include "loaders/GenericLoaderv2.h"

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

using namespace std;

#undef STATIC
#undef VIRTUAL
#define STATIC
#define VIRTUAL

GenericLoaderv2::GenericLoaderv2( std::string imagesFilepath ) {
    if( ManifestLoaderv1::isFormatFor( imagesFilepath ) ) {
        loader = new ManifestLoaderv1( imagesFilepath );
    } else {
        loader = new GenericLoaderv1Wrapper( imagesFilepath );
    }
}

void GenericLoaderv2::load( std::string imagesFilePath, float *images, int *labels, int startN, int numExamples ) {

    unsigned char *ucImages = new unsigned char[ loader->getImageCubeSize() ];
    load( imagesFilePath, ucImages, labels, startN, numExamples );

    int linearSize =  numExamples * loader->getImageCubeSize();

    for( int i = 0; i < linearSize; i++ ) {
        images[i] = ucImages[i];
    }
    delete[] ucImages;
}

void GenericLoaderv2::load( std::string trainFilepath, unsigned char *images, int *labels ) {
    load( trainFilepath, images, labels, 0, 0 );
}

void GenericLoaderv2::load( std::string trainFilepath, unsigned char *images, int *labels, int startN, int numExamples ) {
    StatefulTimer::timeCheck("GenericLoaderv2::load start");

    loader->load( images, labels, startN, numExamples );

    StatefulTimer::timeCheck("GenericLoaderv2::load end");
}


