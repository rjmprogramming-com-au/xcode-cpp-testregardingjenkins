//
//  main.cpp
//  TestRegardingJenkins
//
//  Created by pgAgent on 25/05/2016.
//  Copyright (c) 2016 RJM Programming. All rights reserved.
//
//  WebApplication has a title and web application URL and tutorial of web application URL

#include <iostream>
#include <string>
#include "WebApplication.h"

class WebApplicationRecord {
    char title[201];
    char webApplicationURL[201];
    char tutorialWebApplicationURL[201];
    
public:
    WebApplicationRecord() { strcpy(title,""); strcpy(webApplicationURL,""); strcpy(tutorialWebApplicationURL,"");   };
    WebApplicationRecord(char* xtitle, char* xwebApplicationURL, char* xtutorialWebApplicationURL) {
        strcpy(title, xtitle); strcpy(webApplicationURL, xwebApplicationURL); strcpy(tutorialWebApplicationURL, xtutorialWebApplicationURL);
    }
    ~WebApplicationRecord();
    
    char* getTitle() { return this->title; };
    char* getTutorialURL() { return this->tutorialWebApplicationURL; };
    char* getWebApplicationURL() { return this->webApplicationURL; };
};

class WebApplication {
    int webappsSoFar=0;
    WebApplicationRecord **webapps; // = new WebApplicationRecord*[100000]; //*webapps[20];
    
public:
    WebApplication() {
        webappsSoFar = 0;
        setAside(webappsSoFar);
    }
    
    WebApplication(int askedFor) {
        setAside(askedFor);
        webappsSoFar = 0;
    }
    
    void setAside(int howMany) {
        if (howMany == 0) {
            webapps = new WebApplicationRecord*[100000];
        } else {
            webapps = new WebApplicationRecord*[howMany];
        }
    }
    
    void addToWebapps() {
        webappsSoFar++;
    }
    
    
    void addWebApplication(char* csvbit) {
        WebApplicationRecord *wr;
        char title[201];
        char webApplicationURL[201];
        char tutorialWebApplicationURL[201];
        char *fc1, *fc2;
        if (!strstr(csvbit, ",")) {
            std::cout << "For " << csvbit << " the Web Application URL is " << findURLForWebApplicationViaTitle(csvbit) << " and Tutorial of Web Application URL is " << findURLForTutorialViaTitle(csvbit) << "\n";
        } else {
            fc1=strstr(csvbit, ",");
            *fc1 = 0;
            strcpy(webApplicationURL, csvbit);
            if (!strstr((csvbit + strlen(webApplicationURL) + 1), ",")) {
                *fc1 = ',';
                std::cout << "For " << csvbit << " the Web Application URL is " << findURLForWebApplicationViaTitle(csvbit) << " and Tutorial of Web Application URL is " << findURLForTutorialViaTitle(csvbit) << "\n";
            } else {
                fc2=strstr((csvbit + strlen(webApplicationURL) + 1), ",");
                *fc2 = 0;
                strcpy(tutorialWebApplicationURL, (csvbit + strlen(webApplicationURL) + 1));
                strcpy(title, (csvbit + strlen(tutorialWebApplicationURL) + 1 + strlen(webApplicationURL) + 1));
                *fc1 = ',';
                *fc2 = ',';
                wr = new WebApplicationRecord(title, webApplicationURL, tutorialWebApplicationURL);
                webapps[webappsSoFar] = wr;
                this->addToWebapps(); // webappsSoFar++;
            }
        }
    }
    
    void addWebApplication(char* title, char* webApplicationURL, char* tutorialWebApplicationURL) {
        WebApplicationRecord *wr;
        wr = new WebApplicationRecord(title, webApplicationURL, tutorialWebApplicationURL);
        webapps[webappsSoFar] = wr;
        webappsSoFar++;
    }
    
    char* findURLForTutorial(int which) {
        return webapps[which]->getTutorialURL();
    }
    
    char* findURLForWebApplication(int which) {
        return webapps[which]->getTutorialURL();
        
    }
    
    char* findTitle(int which) {
        return webapps[which]->getTitle();
    }
    
    char* findURLForTutorialViaTitle(char* title) {
        for (int jj=0; jj<webappsSoFar; jj++) {
            int found;
            found = 0 == strcmp(webapps[jj]->getTitle(), title);
            if (found) return webapps[jj]->getTutorialURL();
        }
        return (char *)"";
    }
    
    char* findURLForWebApplicationViaTitle(char* title) {
        for (int jj=0; jj<webappsSoFar; jj++) {
            int found;
            found = 0 == strcmp(webapps[jj]->getTitle(), title);
            if (found) return webapps[jj]->getWebApplicationURL();
        }
        return (char *)"";
    }
    
    ~WebApplication() {
        for (int ii=0; ii<webappsSoFar; ii++) {
            delete webapps[ii];
        }
    }
    
};

char* safe_gets( char* result, int maxchars ) {  // thanks to http://www.cplusplus.com/forum/beginner/22868/
    char  c;
    char* nl;
    
    // Get the user's input (hopefully to EOL)
    fgets( result, maxchars, stdin );
    
    // Strip the newline from the end of the string
    nl = strchr( result, '\n' );
    if (nl) *nl = '\0';
    else
    {
        // Get rid of all remaining characters to newline
        do c = getchar();
        while ((c != EOF) && (c != '\n'));
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    int thisone = 1;
    WebApplication *webapp;
    char thisanswer[601];
    int hm=100000;
    strcpy(thisanswer, "aaa");
    
    std::cout << "Welcome to the Web Application Gatherer Program!\n\nHow many web applications do you expect?\n\n";
    safe_gets(thisanswer, 600);
    hm = atoi(thisanswer);
    webapp = new WebApplication(hm);
    strcpy(thisanswer, "aaa");
    
    while (strlen(thisanswer) > 1) {
        std::cout << "Separate Web Application URL & Tutorial of Web Application URL & Title (longer than 1) " << thisone << " by commas, else we will Find You the URLs for Title you Nominate. Q quits. \n\n";
        //std::cin >> thisanswer;
        safe_gets(thisanswer, 600);
        if (strlen(thisanswer) > 1) {
            webapp->addWebApplication(thisanswer);
        }
    }
    
    std::cout << "Thanks for visiting\n";
    return 0;
}


