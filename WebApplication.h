//
//  WebApplication.h
//  TestRegardingJenkins
//
//  Created by pgAgent on 29/05/2016.
//  Copyright (c) 2016 RJM Programming. All rights reserved.
//

#ifndef WebApplication_WebApplication_h
#define WebApplication_WebApplication_h

void setAside(int howMany);
void addToWebapps();
void addWebApplication();
void addWebApplication(char* title, char* webApplicationURL, char* tutorialWebApplicationURL);
char* findURLForTutorial(int which);
char* findURLForWebApplication(int which);
char* findTitle(int which);
char* findURLForTutorialViaTitle(char* title);
char* findURLForWebApplicationViaTitle(char* title);


#endif
