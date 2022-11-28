#include<bits/stdc++.h>
#include<thread>
using namespace std;

//1: commerce, 2: Humanities, 3: Science, 4: Management
//0: Mcom, 1.Bcom, 2.Phd, 3.Mtech
vector<thread> vt;
map<string, vector<int>> categoryCourses; //category: courses of that category
map<string, vector<int>> branchStudents; //branch: students
map<int, vector<int>> studentPreferences; //student: preferences(course ids)
map<int, vector<int>> studentsAcclocated; //student: category wise alloacted bitMap
map<int, map<int, int>> courseStudentsCount; //course: branch, remaining seats
map<int, int> studentToBranch; //student: branch
map<int, vector<int>> courseAllocated; //student: courses allocated
map<int, int> gotAll; // student: gotAll?(0,1)


void AssignCourses(int s, vector<pthread_mutex_t> *lockArr){

    vector<int> coursesLocked;
    int i = studentToBranch[s];
    // cout<<s<<": "<<i<<endl;
    if(i != 3){
        //allocating Science course
        int firstPreference = studentPreferences[s][0];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        // cout<<"locked "<<s<<" "<<firstPreference<<endl;
        if(courseStudentsCount[firstPreference][i]<12){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][2] = 1;
        }
        if(studentsAcclocated[s][2] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][1];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<12){
                studentsAcclocated[s][2] = 1;
            }
        }
        if(studentsAcclocated[s][2] == 0){
            //capacity of first preference is full, release all
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }
            return;            
        }
        

        //allocating Commerce course
        firstPreference = studentPreferences[s][2];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<12){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][0] = 1;
        }
        if(studentsAcclocated[s][0] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][3];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<12){
                studentsAcclocated[s][0] = 1;
            }
        }
        if(studentsAcclocated[s][0] == 0){
            //capacity of first preference is full, release it
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }
            return;            
        }

        //allocating Humanities course
        firstPreference = studentPreferences[s][4];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<12){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][1] = 1;
        }
        if(studentsAcclocated[s][1] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][5];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<12){
                studentsAcclocated[s][1] = 1;
            }
        }
        if(studentsAcclocated[s][1] == 0){
            //capacity of first preference is full, release it
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }            
            return;
        }


        //allocating Managenent course
        firstPreference = studentPreferences[s][6];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<12){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][3] = 1;
        }
        if(studentsAcclocated[s][3] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][7];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<12){
                studentsAcclocated[s][3] = 1;
            }
        }
        if(studentsAcclocated[s][3] == 0){
            //capacity of first preference is full, release it
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }            
            return;
        }

    }

    if(i == 3){
        //allocating Science course
        int firstPreference = studentPreferences[s][0];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        // cout<<"locked "<<s<<" "<<firstPreference<<endl;
        if(courseStudentsCount[firstPreference][i]<24){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][2] = 1;
        }
        if(studentsAcclocated[s][2] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][1];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<24){
                studentsAcclocated[s][2] = 1;
            }
        }
        if(studentsAcclocated[s][2] == 0){
            //capacity of first preference is full, release all
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }
            return;            
        }


        //allocating Commerce course
        firstPreference = studentPreferences[s][2];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<24){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][0] = 1;
        }
        if(studentsAcclocated[s][0] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][3];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<24){
                studentsAcclocated[s][0] = 1;
            }
        }
        if(studentsAcclocated[s][0] == 0){
            //capacity of first preference is full, release it
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }
            return;            
        }

        //allocating Humanities course
        firstPreference = studentPreferences[s][4];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<24){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][1] = 1;
        }
        if(studentsAcclocated[s][1] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][5];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<24){
                studentsAcclocated[s][1] = 1;
            }
        }
        if(studentsAcclocated[s][1] == 0){
            //capacity of first preference is full, release it
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }            
            return;
        }


        //allocating Managenent course
        firstPreference = studentPreferences[s][6];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<24){

            coursesLocked.push_back(firstPreference);
            studentsAcclocated[s][3] = 1;
        }
        if(studentsAcclocated[s][3] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][7];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            coursesLocked.push_back(secondPreference);

            if(courseStudentsCount[secondPreference][i]<24){
                studentsAcclocated[s][3] = 1;
            }
        }
        if(studentsAcclocated[s][3] == 0){
            //capacity of first preference is full, release it
            int n = coursesLocked.size();
            for(int j=0;j<n;j++){
                pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
            }            
            return;
        }

    }

    //Got all courses, release all
    // cout<<"got all courses "<<s<<endl;
    int n = coursesLocked.size();
    for(int j=0;j<n;j++){
        gotAll[s] = 1;
        courseStudentsCount[coursesLocked[j]][i]++;
        courseAllocated[s].push_back(coursesLocked[j]);

        pthread_mutex_unlock(&lockArr[coursesLocked[j]][i]);
    }            

}

void AssignRemaining(int s, vector<pthread_mutex_t> *lockArr){
    int i = studentToBranch[s];
    // cout<<s<<": "<<i<<endl;
    if(i != 3){
        //allocating Science course
        int firstPreference = studentPreferences[s][0];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        //cout<<"locked "<<s<<" "<<firstPreference<<endl;
        if(courseStudentsCount[firstPreference][i]<12){
            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][2] = 1;
        }
        if(studentsAcclocated[s][2] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][1];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            if(courseStudentsCount[secondPreference][i]<12){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][2] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
            
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }



        //allocating Commerce course
        firstPreference = studentPreferences[s][2];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<12){

            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][0] = 1;
        }
        if(studentsAcclocated[s][0] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][3];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);

            if(courseStudentsCount[secondPreference][i]<12){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][0] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }

        //allocating Humanities course
        firstPreference = studentPreferences[s][4];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<12){

            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][1] = 1;
        }
        if(studentsAcclocated[s][1] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][5];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);

            if(courseStudentsCount[secondPreference][i]<12){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][1] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }

        //allocating Managenent course
        firstPreference = studentPreferences[s][6];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<12){

            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][3] = 1;
        }
        if(studentsAcclocated[s][3] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][7];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);

            if(courseStudentsCount[secondPreference][i]<12){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][3] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }
    }

    if(i == 3){
        //allocating Science course
        int firstPreference = studentPreferences[s][0];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        //cout<<"locked "<<s<<" "<<firstPreference<<endl;
        if(courseStudentsCount[firstPreference][i]<24){
            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][2] = 1;
        }
        if(studentsAcclocated[s][2] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][1];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);
            if(courseStudentsCount[secondPreference][i]<24){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][2] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }


        //allocating Commerce course
        firstPreference = studentPreferences[s][2];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<24){

            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][0] = 1;
        }
        if(studentsAcclocated[s][0] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][3];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);

            if(courseStudentsCount[secondPreference][i]<24){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][0] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }

        //allocating Humanities course
        firstPreference = studentPreferences[s][4];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<24){

            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][1] = 1;
        }
        if(studentsAcclocated[s][1] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][5];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);

            if(courseStudentsCount[secondPreference][i]<24){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][1] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }

        //allocating Managenent course
        firstPreference = studentPreferences[s][6];

        //taking lock on first preference
        pthread_mutex_lock(&lockArr[firstPreference][i]);
        if(courseStudentsCount[firstPreference][i]<24){

            courseStudentsCount[firstPreference][i]++;
            courseAllocated[s].push_back(firstPreference);
            studentsAcclocated[s][3] = 1;
        }
        if(studentsAcclocated[s][3] == 0){
            //capacity of first preference is full, release it
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
            
            int secondPreference = studentPreferences[s][7];

            //take lock on second pref
            pthread_mutex_lock(&lockArr[secondPreference][i]);

            if(courseStudentsCount[secondPreference][i]<24){

                courseStudentsCount[secondPreference][i]++;
                courseAllocated[s].push_back(secondPreference);
                studentsAcclocated[s][3] = 1;
            }
            pthread_mutex_unlock(&lockArr[secondPreference][i]);
        }
        else{
            pthread_mutex_unlock(&lockArr[firstPreference][i]);
        }
    }
}

int main(int args, char **argv){
    int students = stoi(argv[1]), courses = stoi(argv[2]);
    // cin>>students>>courses;
    int x = courses/4;
    
    
    vector<pthread_mutex_t> lockArr[courses];
    for(int i=0;i<courses;i++){
        for(int j=0;j<4;j++){
            pthread_mutex_t x;
            lockArr[i].push_back(x);
            pthread_mutex_init(&lockArr[i][j], NULL);
        }
    }
    
    for(int i=0;i<x;i++){
        categoryCourses["Commerce"].push_back(i);
    }
    for(int i=x;i<2*x;i++){
        categoryCourses["Humanities"].push_back(i);
    }
    for(int i=2*x;i<3*x;i++){
        categoryCourses["Science"].push_back(i);
    }
    for(int i=3*x;i<4*x;i++){
        categoryCourses["Management"].push_back(i);
    }
    
    int rem = courses % 4;
    if(rem>0){
        categoryCourses["Management"].push_back(courses-rem);
        rem--;
    }
    if(rem>0){
        categoryCourses["Science"].push_back(courses-rem);
        rem--;
    }
    if(rem>0){
        categoryCourses["Commerce"].push_back(courses-rem);
        rem--;
    }

    // for(auto it: categoryCourses){
    //     cout<<it.first<<" "<<it.second.size()<<endl;
    // }

    int y = students/5;
    for(int i=0;i<y;i++){
        branchStudents["Mcom"].push_back(i);
        studentToBranch[i] = 0;
    }
    for(int i=y;i<2*y;i++){
        branchStudents["Bcom"].push_back(i);
        studentToBranch[i] = 1;
    }
    for(int i=2*y;i<3*y;i++){
        branchStudents["Phd"].push_back(i);
        studentToBranch[i] = 2;
    }
    for(int i=3*y;i<5*y;i++){
        branchStudents["Mtech"].push_back(i);
        studentToBranch[i] = 3;
    }
    
    rem = students % 5;
    if(rem>0){
        branchStudents["Mcom"].push_back(students-rem);
        studentToBranch[students-rem] = 0;
        rem--;
    }
    if(rem>0){
        branchStudents["Bcom"].push_back(students-rem);
        studentToBranch[students-rem] = 1;
        rem--;
    }
    if(rem>0){
        branchStudents["Phd"].push_back(students-rem);
        studentToBranch[students-rem] = 2;
        rem--;
    }
    if(rem>0){
        branchStudents["Mtech"].push_back(students-rem);
        studentToBranch[students-rem] = 3;
        rem--;
    }

    cout<<endl;
    // for(auto it: branchStudents){
    //     cout<<it.first<<" "<<it.second.size()<<endl;
    // }

    for(int i=0;i<students;i++){

        //2 preferences for science
        int science = categoryCourses["Science"][ rand() % categoryCourses["Science"].size() ];
        studentPreferences[i].push_back(science);
        int secScience = categoryCourses["Science"][ rand() % categoryCourses["Science"].size() ];
        while(secScience == science)
            secScience = categoryCourses["Science"][ rand() % categoryCourses["Science"].size() ];
        studentPreferences[i].push_back(secScience);

        //2 preferences for Commerce
        int Commerce = categoryCourses["Commerce"][ rand() % categoryCourses["Commerce"].size() ];
        studentPreferences[i].push_back(Commerce);
        int secCommerce = categoryCourses["Commerce"][ rand() % categoryCourses["Commerce"].size() ];
        while(secCommerce == Commerce)
            secCommerce = categoryCourses["Commerce"][ rand() % categoryCourses["Commerce"].size() ];
        studentPreferences[i].push_back(secCommerce);

        //2 preferences for Humanities
        int Humanities = categoryCourses["Humanities"][ rand() % categoryCourses["Humanities"].size() ];
        studentPreferences[i].push_back(Humanities);
        int secHumanities = categoryCourses["Humanities"][ rand() % categoryCourses["Humanities"].size() ];
        while(secHumanities == Humanities)
            secHumanities = categoryCourses["Humanities"][ rand() % categoryCourses["Humanities"].size() ];
        studentPreferences[i].push_back(secHumanities);

        //2 preferences for Management
        int Management = categoryCourses["Management"][ rand() % categoryCourses["Management"].size() ];
        studentPreferences[i].push_back(Management);
        int secManagement = categoryCourses["Management"][ rand() % categoryCourses["Management"].size() ];
        while(secManagement == Management)
            secManagement = categoryCourses["Management"][ rand() % categoryCourses["Management"].size() ];
        studentPreferences[i].push_back(secManagement);

    }    


    // for(auto it: studentPreferences){
    //     cout<<it.first<<" "<<it.second.size()<<endl;
    // }
    // cout<<endl;
    // for(int i=0;i<students;i++){
    //     for(int j=0;j<studentPreferences[i].size();j++){
    //         cout<<studentPreferences[i][j]<<" ";
    //     }
    //     cout<<endl<<endl;
    // }

    vector<int> s;
    for(int i=0;i<students;i++){
        s.push_back(i);
    }
    random_shuffle(s.begin(), s.end());

    for(int i=0;i<students;i++){
        for(int j=0;j<4;j++){
            studentsAcclocated[s[i]].push_back(0);
        }
        vt.push_back(thread(AssignCourses, s[i], &lockArr[0]));
    }

    int n = vt.size();
    for(int i=0;i<n;i++){
        if(vt[i].joinable())vt[i].join();
    }
    // for(int i=0;i<students;i++){
    //     cout<<i<<": "<<studentToBranch[i]<<endl;
    // }

    // cout<<courseAllocated.size();
    cout<<"\nStudents left: "<<students-courseAllocated.size()<<endl;

	ofstream tmpFile;
	tmpFile.open("allocation.txt", ios :: out);
    
    for(int i=0;i<courses;i++){
    	int ans = 0;
    	for(auto it:courseStudentsCount[i]){
    		ans += it.second;
    	}
	    tmpFile << "Course " <<i<< ": "<<ans<<endl;
    	
    }
	
    tmpFile << "-------------After assigning remaining Courses----------------"<<endl;

    vt.clear();
    cout<<"Student Ids of Left Students\n";
    for(int i=0;i<students;i++){
        if(gotAll.find(s[i]) == gotAll.end() || gotAll[s[i]] == 0){
            cout<<s[i]<<endl;
            vt.push_back(thread(AssignRemaining, s[i], &lockArr[0]));
        }
    }

    n = vt.size();
    for(int i=0;i<n;i++){
        if(vt[i].joinable())vt[i].join();
    }

    for(int i=0;i<courses;i++){
    	int ans = 0;
    	for(auto it:courseStudentsCount[i]){
    		ans += it.second;
    	}
	    tmpFile << "Course " <<i<< ": "<<ans<<endl;
    	
    }

	tmpFile.close();

    // for(auto it: courseAllocated){
    //     cout<<it.first<<": ";
    //     for(int i=0;i<it.second.size();i++){
    //         cout<<it.second[i]<<" ";
    //     }
    //     cout<<endl; 
    // }
    return 0;
}
