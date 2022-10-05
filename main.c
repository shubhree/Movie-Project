#include <stdio.h>
#include "gryphflix.h"


// driver code.
int main()
{




//    FILE *ourFile = openFileForReading("myText.txt");
    FILE *movieFile = openFileForReading("movies.txt");

//    while(fgets(dataToBeRead, 50, ourFile)!=NULL){
//        printf("%s", dataToBeRead);
//    }
//    while(1){
//        char characterRead = fgetc(ourFile);
//        if(characterRead == '\n'){
//            continue;
//        }
//        if(characterRead == EOF){
//            break;
//        }
//        printf("%c",characterRead);
//    }


    char movieData[NUMBER_MOVIES][MAX_STR];
    int done = readMovies(movieFile, movieData);

    if(done == 1){
        printf("%s", movieData[0]);
        printf("%s", movieData[1]);
        printf("%s", movieData[2]);
    }else{
        printf("error in reading");
    }


//    struct reviewStruct reviews[NUMBER_REVIEWERS];
//    char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR];

//    int done = readReviews(ourFile, reviews);
//    if(done){
//        printf("%d", reviews[0].feedback[0]);
//        printf("%d", reviews[0].feedback[1]);
//        printf("%d", reviews[0].feedback[2]);
//    }else{
//        printf("There's an error.");
//    }

//    int criticalCount = getMostCriticalReviewers(reviews, mostCriticalReviewers);
//    printf("%d", criticalCount);
//    int criticalIndex = 0;
//    for(criticalIndex = 0; criticalIndex < criticalCount; criticalIndex ++){
//        printf("%s", mostCriticalReviewers[criticalIndex]);
//    }


//    char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR];
//    char moviesArray[NUMBER_MOVIES][MAX_STR];
//
//    int moviesRead = readMovies(movieFile, moviesArray);
//
//    if(moviesRead){
//        printf("%d", predictMovie(moviesArray[0]));
//    }
//
//    int mostRecommendedMoviesCount = getMostRecommendedMovies(moviesArray, reviews, mostRecommendedMovies);
//
//    for(int mostRecommendedMoviesIndex = 0; mostRecommendedMoviesIndex < mostRecommendedMoviesCount; mostRecommendedMoviesIndex ++){
//        printf("%s", mostRecommendedMovies[mostRecommendedMoviesIndex]);
//    }

    return 0;
}
