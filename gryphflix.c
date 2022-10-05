#include <stdio.h>
#include <string.h>
#include "gryphflix.h"

// A function that would be responsible for opening files in read-only mode.
FILE *openFileForReading(char* fileName){
    FILE *filePointer = fopen(fileName, "r");
    return filePointer;
}

//This function will be responsible for reading movies from movies file and storing them in array.
// Incredibles....


int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR]){

    if(file == NULL){

        return 0;
    }

    int movieIndex = 0;
    int characterIndex = 0;
    int movieEndFlag = 0;
    while(1){

        char characterRead = fgetc(file);
        if(characterRead == EOF){
            break;
        }
        if(movieIndex >= NUMBER_MOVIES){
            return 0;
        }
        if(characterRead == '\n'){
            characterRead = '\0';
            movieEndFlag = 1;
        }

        movieNames[movieIndex][characterIndex] = characterRead;
        if(movieEndFlag == 1){
            movieIndex += 1;
            characterIndex = 0;
            movieEndFlag = 0;
        }else{
            characterIndex += 1;
        }
    }
    if(movieIndex != NUMBER_MOVIES){

        return 0;
    }
    return 1;
}

// This function is used for reading and organizing reviews by people into structures.
int readReviews(FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS]){

    if(file == NULL){
        return 0;
    }

    int reviewerIndex = 0;
    int movieIndex = 0;
    int nameIndex = 0;
    int state = 0;
    while(1){
        char characterRead = fgetc(file);
        if(characterRead == EOF){
            break;
        }

        if(reviewerIndex >= NUMBER_REVIEWERS){
            return 0;
        }

        if(characterRead == '\n'){
            reviewerIndex += 1;
            movieIndex = 0;
            state = 0;
            nameIndex = 0;
            continue;
        }

        if(characterRead == ' '){
            state += 1;
            continue;
        }

        if(state == 0){
            reviews[reviewerIndex].reviewer[nameIndex] = characterRead;
            nameIndex += 1;
        }else{
            if(characterRead == 'y' || characterRead == 'Y'){
                reviews[reviewerIndex].feedback[movieIndex] = 1;
            }else{
                reviews[reviewerIndex].feedback[movieIndex] = 0;
            }

            movieIndex += 1;
        }

    }
    if(reviewerIndex != NUMBER_REVIEWERS){

        return 0;
    }
    return 1;
}


// Used to get list of people giving most critical reviews. It returns the number of maximum critical reviews.
int getMostCriticalReviewers(struct reviewStruct reviews[], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR]){
    int criticalCount = 0;
    int reviewerIndex = 0;
    int movieIndex = 0;
    int criticalReviewerIndex = 0;
    for(reviewerIndex = 0; reviewerIndex < NUMBER_REVIEWERS; reviewerIndex += 1){
        int negativeCount = 0;
        for(movieIndex = 0; movieIndex < NUMBER_MOVIES; movieIndex += 1){
            if(reviews[reviewerIndex].feedback[movieIndex] == 0){
                negativeCount += 1;
            }
        }
        if(negativeCount > criticalCount){
            criticalCount = negativeCount;
        }
    }
    for(reviewerIndex = 0; reviewerIndex < NUMBER_REVIEWERS; reviewerIndex += 1){
        int negativeCount = 0;
        for(movieIndex = 0; movieIndex < NUMBER_MOVIES; movieIndex += 1){
            if(reviews[reviewerIndex].feedback[movieIndex] == 0){
                negativeCount += 1;
            }
        }
        if(negativeCount == criticalCount){
            strcpy(mostCriticalReviewers[criticalReviewerIndex], reviews[reviewerIndex].reviewer);
            criticalReviewerIndex += 1;

        }
    }
    return criticalReviewerIndex;

}

// Helps in getting a list of movies that have been recommended most.
int getMostRecommendedMovies(const char movies[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR]){
    int recommendCount[NUMBER_MOVIES];
    int maxRecommendCount = 0;
    int reviewerIndex = 0;
    int movieIndex = 0;
    int recommendCountIndex = 0;
    int mostRecommendedMoviesIndex = 0;

    for(recommendCountIndex = 0; recommendCountIndex < NUMBER_MOVIES; recommendCountIndex ++){
        recommendCount[recommendCountIndex] = 0;
    }

    for(reviewerIndex = 0; reviewerIndex < NUMBER_REVIEWERS; reviewerIndex ++){
        for(movieIndex = 0; movieIndex < NUMBER_MOVIES; movieIndex ++){
            recommendCount[movieIndex] += (reviews[reviewerIndex].feedback[movieIndex]);
        }
    }

    for(recommendCountIndex = 0; recommendCountIndex < NUMBER_MOVIES; recommendCountIndex ++){

        if(recommendCount[recommendCountIndex]>maxRecommendCount){
            maxRecommendCount = recommendCount[recommendCountIndex];

        }
    }

//    printf("%d", maxRecommendCount);

    for(recommendCountIndex = 0; recommendCountIndex < NUMBER_MOVIES; recommendCountIndex ++){
        if(recommendCount[recommendCountIndex] == maxRecommendCount){
            strcpy(mostRecommendedMovies[mostRecommendedMoviesIndex], movies[recommendCountIndex]);
            mostRecommendedMoviesIndex += 1;
        }
    }
    return mostRecommendedMoviesIndex;

}

// Counts words in movie name.
int checkWordsInMovieName(const char name[MAX_STR]){
    int wordCount = 0;
    int index = 0;
    while(name[index]!= '\0'){
        if(name[index] == ' '){
            wordCount += 1;
        }
        index += 1;
    }
    return wordCount + 1;
}

// Responsible for counting words that have even number of characters.
int countCharactersInName(const char name[MAX_STR]){
    int wordsWithEven = 0;
    int currentWordCount = 0;
    int index = 0;
    while(name[index] != '\0'){
        if(name[index] != ' '){
            currentWordCount += 1;
        }
        if(name[index] == ' ' || name[index + 1] == '\0'){
            if(currentWordCount % 2 == 0){
                wordsWithEven += 1;
            }
            currentWordCount = 0;
        }
        index += 1;
    }
    return wordsWithEven;
}

// it checks if each character has same number of characters.
int checkCharactersEachWord(const char name[MAX_STR]){
    int previousWordCount = 0;
    int currentWordCount = 0;
    int index = 0;
    while(name[index] != '\0'){
        if(name[index] != ' '){
            currentWordCount += 1;
        }
        if(name[index] == ' ' || name[index + 1] == '\0'){

            if(previousWordCount != 0 && currentWordCount != previousWordCount){
                return 0;
            }else{
                previousWordCount = currentWordCount;
                currentWordCount = 0;
                index += 1;
                continue;
            }
        }
        index += 1;
    }
    return 1;

}

// calculates/predicts the future performance of the movie based on given algorithm.
int predictMovie(const char movie[MAX_STR]){
    int prediction = 0;
    int wordCount = checkWordsInMovieName(movie);
    int countWordsEvenCharacters = countCharactersInName(movie);
    int hasSameNumberCharacters = checkCharactersEachWord(movie);
    if(wordCount == 1){
        prediction -= 2;
    }
    if(wordCount > 2){
        prediction -= 1;
    }
    if(countWordsEvenCharacters > 1){
        prediction += 1;
    }
    if(hasSameNumberCharacters){
        prediction += 2;
    }

    if(prediction > 2){
        return 2;
    }else if(prediction < -2){
        return -2;
    }else{
        return prediction;
    }
}

