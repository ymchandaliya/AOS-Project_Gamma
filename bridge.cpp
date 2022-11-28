#include<iostream>
#include<string>
#include<vector>
#include "logger.h"

#include <pthread.h>
using namespace std;

string opg = " Geek      ";
string opng = " Non-Geek  " ;
string ops = " Singer    " ;

    // ================================================================================ ||
    //                        Functionalities For Arrivals                              ||
    // ================================================================================ ||


// Varibles For Bridge Status
pthread_mutex_t bridge_state;
struct BridgeStatus
{

    // Count of Elements that present on bridge
    int Geeks1;
    int Singers;
    int NonGeeks1;
    int currentLoad;
    string Bridge[4];

    // Count of Elements available
    int totalGeek;
    int totalNonGeek;
    int totalSinger;
    int totalPass;

    // Variable that hold capacity for last iteration
    int dy_last_cap;
    int lastPassCapacity;

    bool only_singers_exists;
    
    BridgeStatus(){
    this->Geeks1 = 0 ;
    this->NonGeeks1 = 0 ;
    this->currentLoad  = 0;
    this->Singers = 0;
    this->dy_last_cap = -1 ;
    this->only_singers_exists = false;
    }

};
BridgeStatus* bridge_data = new BridgeStatus();

// Variables For wait and Broadcast when Full Load
pthread_cond_t full_load;
pthread_mutex_t go_bridge;


// Varible to Wait For Another One to Come
pthread_cond_t g_w;
pthread_mutex_t geek_wait;

pthread_cond_t ng_w;
pthread_mutex_t ngeek_wait;

pthread_cond_t singer_w;
pthread_mutex_t singer_wait;



void Go_Bridge()
{
        string ans = "";
    for(int i = 0 ; i < bridge_data->currentLoad ;i++ ){
        if(bridge_data->Bridge[i] == opg)bridge_data->totalGeek -= 1 ;
        if(bridge_data->Bridge[i] == opng)bridge_data->totalNonGeek -= 1 ;
        if(bridge_data->Bridge[i] == ops)bridge_data->totalSinger -= 1 ;
        ans += bridge_data->Bridge[i] ;
        
    }
    Log::Info(ans);
    cout<<ans<<endl;
    Log::Info("------------------------------------------------------");
    bridge_data->totalPass -= bridge_data->currentLoad ;
    bridge_data->currentLoad  = 0;
    bridge_data->Geeks1 = 0;
    bridge_data->NonGeeks1 = 0;
    bridge_data->Singers = 0;
    // pthread_mutex_unlock(&bridge_state);

    pthread_mutex_unlock(&bridge_state);

    Log::Warn("Broadcasted ... ");
    pthread_mutex_lock(&go_bridge);
    pthread_cond_broadcast(&full_load);
    pthread_mutex_unlock(&go_bridge);
}

            //=======================================================//
           //                      Geek Arrives                     //
          //=======================================================//

void* GeekArrives(void* para){
    // Log::Info("Geek Arrived ....");

    
    while(true){
    
        // Log::Info("Geek Enteredd in Crical Section");
        pthread_mutex_lock(&bridge_state);
        // Log::Info("Geek Taken Boat Lock");
        
        if(bridge_data->Singers == 1  && bridge_data->currentLoad < 4){   
            // if signger available or sleeping singer is there then
            bridge_data->Bridge[bridge_data->currentLoad++] = opg;
            bridge_data->Geeks1 += 1 ;
            // Log::Info("geek besi gayo");
            break;
        }
        else if(bridge_data->totalGeek == 1 && bridge_data->totalPass > bridge_data->lastPassCapacity){
            pthread_mutex_unlock(&bridge_state);
        }
        else if(bridge_data->currentLoad == 3 && (bridge_data->Geeks1 == 2 || bridge_data->NonGeeks1 == 3 )){   
            // if signger available or sleeping singer is there then
            pthread_mutex_unlock(&bridge_state);
        }
        else{
            // if another Geek is Waiting then make a pair and add them to Boat
            bridge_data->Bridge[bridge_data->currentLoad++] = opg;
            bridge_data->Geeks1 += 1 ;
            // Log::Info("geek besi gayo");
            break;
        }


    }

    Log::Info("Geat Seated");
    if(bridge_data->lastPassCapacity == bridge_data->currentLoad && bridge_data->lastPassCapacity == bridge_data->totalPass){

       Go_Bridge();

    }
    else if(bridge_data->totalGeek+bridge_data->totalNonGeek < 3 && bridge_data->totalSinger > 1 ){
        if(bridge_data->dy_last_cap == -1){
            bridge_data->dy_last_cap = bridge_data->totalGeek+bridge_data->totalNonGeek+1;
        }
        if(bridge_data->currentLoad == bridge_data->dy_last_cap){
            bridge_data->only_singers_exists = true;
            Go_Bridge();
        }
        else{
            pthread_mutex_unlock(&bridge_state);
            Log::Info("Broadcast Wait g8eek ...");
            pthread_mutex_lock(&go_bridge);
            pthread_cond_wait(&full_load,&go_bridge);
            pthread_mutex_unlock(&go_bridge);
            Log::Info("Broadcast k reelse Wait g8eek  ...");
        }
    }
    else if((bridge_data->totalPass == 4) && ((bridge_data->totalGeek == 3  && bridge_data->totalNonGeek == 1)  || (bridge_data->totalGeek == 1  && bridge_data->totalNonGeek == 3)) && (bridge_data->totalSinger == 0)){
        bridge_data->lastPassCapacity = 3 ;
        Go_Bridge();
    }
    else if(bridge_data->currentLoad == 4){

        //================================//
        //          Board Bridge ()       //
        // ===============================//

        
        //================================//
        //          Go Bridge ()          //
        // ===============================//
        
        // pthread_mutex_lock(&bridge_state);

       Go_Bridge();
    }
    else{
        // boardBridge() and Now Wait For GoBridge to start the Journy
        pthread_mutex_unlock(&bridge_state);

        //================================//
        //          Board Bridge ()       //
        // ===============================//

        pthread_mutex_lock(&go_bridge);
            Log::Info("Broadcast Wait g8eek ...");
        pthread_cond_wait(&full_load,&go_bridge);
        pthread_mutex_unlock(&go_bridge);
            Log::Info("Broadcast k reelse Wait g8eek  ...");
            
        //================================//
        //          Go Bridge ()          //
        // ===============================//

    }
    Log::Info("ogeek pochi gayo");
    return NULL;

}



             //======================================================//
            //                   Non Geek Arrives                   //
           //======================================================//
void* NonGeekArrives(void* para){
    Log::Info("Non Geek Arrived ....");

    
    while(true){
    
        // Log::Info("Geek Enteredd in Crical Section");
        pthread_mutex_lock(&bridge_state);
        Log::Info("Non Geek Taken Boat Lock");
        
        if(bridge_data->Singers == 1  && bridge_data->currentLoad < 4){   
            // if signger available and empty space is there...  
            // Log::Info("ngeek besi gayo");
            bridge_data->Bridge[bridge_data->currentLoad++] = opng;
            bridge_data->NonGeeks1 += 1 ;
            break;
        }
        else if(bridge_data->totalNonGeek == 1 && bridge_data->totalPass > bridge_data->lastPassCapacity){
            // there are 1 remaining and not last pass tnen wait (1-3-0)
            pthread_mutex_unlock(&bridge_state);
        }
        else if(bridge_data->currentLoad == 3 && (bridge_data->NonGeeks1 == 2 || bridge_data->Geeks1 == 3)){   
            // if currently 3 there then wait for case (3-0-0) or (1-2-0)
            pthread_mutex_unlock(&bridge_state);
        }
        else{
            // if another Geek is Waiting then make a pair and add them to Boat
            // Log::Info("ngeek besi gayo");
            bridge_data->Bridge[bridge_data->currentLoad++] = opng;
            bridge_data->NonGeeks1 += 1 ;
            break;
        }


    }
    
    Log::Info("NOn geek4 Seated");
    if(bridge_data->lastPassCapacity == bridge_data->currentLoad && bridge_data->lastPassCapacity == bridge_data->totalPass){
        Go_Bridge();
    }
    else if(bridge_data->totalGeek+bridge_data->totalNonGeek < 3 && bridge_data->totalSinger > 1 ){
        if(bridge_data->dy_last_cap == -1){
            bridge_data->dy_last_cap = bridge_data->totalGeek+bridge_data->totalNonGeek+1;
        }
        if(bridge_data->currentLoad == bridge_data->dy_last_cap){
            bridge_data->only_singers_exists = true;
            Go_Bridge();
        }
        else{
            pthread_mutex_unlock(&bridge_state);
            pthread_mutex_lock(&go_bridge);
            Log::Info("Broadcast Wait ng8eek ...");
            pthread_cond_wait(&full_load,&go_bridge);
            pthread_mutex_unlock(&go_bridge);
            Log::Info("Broadcast k reelse Wait ng8eek  ...");
        }
    }
    else if((bridge_data->totalPass == 4) && ((bridge_data->totalGeek == 3  && bridge_data->totalNonGeek == 1)  || (bridge_data->totalGeek == 1  && bridge_data->totalNonGeek == 3)) && (bridge_data->totalSinger == 0)){
        bridge_data->lastPassCapacity = 3 ;
        Go_Bridge();
    }
    else if(bridge_data->currentLoad == 4){

        //================================//
        //          Board Bridge ()       //
        // ===============================//

        
        //================================//
        //          Go Bridge ()          //
        // ===============================//
        
        // pthread_mutex_lock(&bridge_state);

        Go_Bridge();
    }
    else{
        pthread_mutex_unlock(&bridge_state);
        // boardBridge() and Now Wait For GoBridge to start the Journy

        //================================//
        //          Board Bridge ()       //
        // ===============================//

        pthread_mutex_lock(&go_bridge);
            Log::Info("Broadcast Wait ng8eek ...");
        pthread_cond_wait(&full_load,&go_bridge);
        pthread_mutex_unlock(&go_bridge);
            Log::Info("Broadcast k reelse Wait ng8eek  ...");

        // Log::Info("Broadcast Rleased ...");

        //================================//
        //          Go Bridge ()          //
        // ===============================//

    }
    Log::Info("ngeek pochi gayo");
    return NULL;

}


            //=======================================================//
           //                    Singer Arrives                    //
          //=====================================================//

void* SingerArrives(void* para){

    while(true){
    
        // Log::Info("Geek Enteredd in Crical Section");
        pthread_mutex_lock(&bridge_state);
        // Log::Info("Non Geek Taken Boat Lock");
        
        if(bridge_data->Singers == 0 && bridge_data->currentLoad < 4){   
            // if signger available or sleeping singer is there then
            // Log::Info("Singer besi gayo");
            bridge_data->Bridge[bridge_data->currentLoad++] = ops;
            bridge_data->Singers += 1 ;
            if(bridge_data->totalGeek+bridge_data->totalNonGeek == 0)
                bridge_data->only_singers_exists = true;
            break;
        }
        else{   
            // if signger available or sleeping singer is there then
            pthread_mutex_unlock(&bridge_state);
        }
    }
    
    Log::Info("Snig seated");
    if(bridge_data->lastPassCapacity == bridge_data->currentLoad && bridge_data->lastPassCapacity == bridge_data->totalPass){
        Go_Bridge();
    }
    else if(bridge_data->only_singers_exists){
        Go_Bridge();
    }
    else if(bridge_data->currentLoad == 4){

        //================================//
        //          Board Bridge ()       //
        // ===============================//

        
        //================================//
        //          Go Bridge ()          //
        // ===============================//
        
        // pthread_mutex_lock(&bridge_state);
        Go_Bridge();
    }
    else{
        pthread_mutex_unlock(&bridge_state);
        // boardBridge() and Now Wait For GoBridge to start the Journy

        //================================//
        //          Board Bridge ()       //
        // ===============================//

        pthread_mutex_lock(&go_bridge);
            Log::Info("Broadcast Wait sing ...");
        pthread_cond_wait(&full_load,&go_bridge);
        pthread_mutex_unlock(&go_bridge);
            Log::Info("Broadcast k reelse Wait sing  ...");

        // Log::Info("Broadcast Rleased ...");

        //================================//
        //          Go Bridge ()          //
        // ===============================//

    }
    Log::Info("singdano pochi gayo");
    return NULL;
}


int main(int argc, char **argv)
{

    ofstream log_file("logFile.txt", ios_base::out | ios_base::trunc );

    pthread_mutex_init(&bridge_state, NULL);

    pthread_mutex_init(&go_bridge, NULL);
    pthread_cond_init(&full_load,NULL);

    pthread_mutex_init(&geek_wait, NULL);
    pthread_cond_init(&g_w,NULL);

    pthread_mutex_init(&singer_wait, NULL);
    pthread_cond_init(&singer_w,NULL);

    // Log::Info("Programme Started ...");


    int numGeeks = stoi(argv[1]) ;
    int numNonGeeks = stoi(argv[2]) ;
    int numSinger = stoi(argv[3]) ;
    
    bridge_data->totalGeek = numGeeks;
    bridge_data->totalNonGeek = numNonGeeks;
    bridge_data->totalSinger = numSinger;

    // Data For Last Pass
    bridge_data->totalPass = numGeeks + numNonGeeks + numSinger ;
    bridge_data->lastPassCapacity = bridge_data->totalPass%4;
    if(bridge_data->lastPassCapacity == 0){
        bridge_data->lastPassCapacity = 4;
    }
    // cout<<bridge_data->lastPassCapacity<<endl;
    // cout<<numGeeks + numNonGeeks + numSinger<<endl; 
    pthread_t calling[1000];
    int cont = 0 ;
    int tr = max(numGeeks,max(numNonGeeks,numSinger));
    // cout<<tr<<endl;
    for(int i = 0 ; i < tr ; i++ ){
        if(numGeeks-- > 0 )pthread_create(&calling[cont++],NULL,GeekArrives,NULL);
        if(numNonGeeks-- > 0 )pthread_create(&calling[cont++],NULL,NonGeekArrives,NULL);
        if(numSinger-- > 0 ) pthread_create(&calling[cont++],NULL,SingerArrives,NULL);
    }

    for(int i = 0 ; i < cont ; i++ ){
        pthread_join(calling[i],NULL);
    }
    // cout<<endl;
    return 0 ;

}
