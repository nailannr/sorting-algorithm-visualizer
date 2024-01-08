#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#define endl '\n'

using namespace std;

const int arrSize = 100;
const int rectWidth = 10;
const int screenHeight = 500;
const int screenWidth = arrSize*rectWidth;
const int delayPeriod = 50;

int moves = 0;
bool finished = false;
bool close = false;

vector<int>generatedArray(arrSize);
vector<int>storedArray(arrSize);

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event global_ev;

void quit(){
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
    return;
}

void sortVisualizer(int x=-1, int y=-1)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int j=0;
    for(int i=0; i<screenWidth; i+=rectWidth)
    {
        SDL_PumpEvents();

        SDL_Rect rect;
        rect.x = i;
        rect.y= screenHeight-storedArray[j];
        rect.h = storedArray[j];
        rect.w = rectWidth;

        if(finished)
        {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        else if(j==x)
        {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if(j==y)
        {
            SDL_SetRenderDrawColor(renderer, 165, 105, 189, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);
}

void bubbleSort()
{
    for(int i=0; i<arrSize-1; i++)
    {
        bool flag = false;
        for(int j=0; j<arrSize-1-i; j++)
        {

             while(SDL_PollEvent(&global_ev) != 0){
                if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                    close = true;
                    return;
                }
             }
            moves++;
            if(storedArray[j+1]<storedArray[j])
            {
                swap(storedArray[j],storedArray[j+1]);

                sortVisualizer(j+1, j);
                flag = true;
            }
           SDL_Delay(delayPeriod);
        }

        if(!flag) break;
    }
}

void insertionSort(){
    for(int i=1; i<arrSize; i++){
        int j= i-1;
        int temp = storedArray[i];

        while(j>=0 && storedArray[j]>temp){
            while(SDL_PollEvent(&global_ev) != 0){
                if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                    close = true;
                    return;
                }
            }
            storedArray[j+1] = storedArray[j];
            j--;

            sortVisualizer(i,j+1);
            SDL_Delay(delayPeriod);
            moves++;
        }
        storedArray[j+1] = temp;
    }
}

int findLocation(int lowerBound){
    int location = lowerBound;
    for(int i=lowerBound+1; i<arrSize;i++){
        while(SDL_PollEvent(&global_ev) != 0){
            if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                close = true;
                return -1;
            }
        }
        if(storedArray[location]>storedArray[i]){
            location = i;
            sortVisualizer(lowerBound,location);
        }
        SDL_Delay(delayPeriod);
        moves++;
    }

    return location;
}

void selectionSort(){    
    for(int i=0;i<arrSize-1; i++){
        int minNumLocation = findLocation(i);
        if(minNumLocation == -1) return;
        if(minNumLocation != i){
            swap(storedArray[minNumLocation], storedArray[i]);
        }
    }
}

void merge(vector<int>&v, int left, int mid, int right) {
	int leftSize = mid - left + 1;
	int rightSize = right - mid;
	int size = right - left + 1;

	vector<int> tempArrayLeft(leftSize);
	vector<int> tempArrayRight(rightSize);
	vector<int> tempArray(size);

	for (int i = 0; i < leftSize; i++) {
		tempArrayLeft[i] = v[left + i];
	}

	for (int i = 0; i < rightSize; i++) {
		tempArrayRight[i] = v[mid + i + 1];
	}

	int i = 0, j = 0, k = 0;

	while (i < leftSize && j < rightSize) {
		if (tempArrayLeft[i] <= tempArrayRight[j]) {
			tempArray[k] = tempArrayLeft[i];
			sortVisualizer(left+i,mid+1+j);
            SDL_Delay(delayPeriod);
			i++;
			k++;
            moves++;
		}
		else {
			tempArray[k] = tempArrayRight[j];
			sortVisualizer(left+i,mid+1+j);
            SDL_Delay(delayPeriod);
			j++;
			k++;
            moves++;
		}
	}

	while (i < leftSize) {
		tempArray[k] = tempArrayLeft[i];
		sortVisualizer(-1,left+i);
        SDL_Delay(delayPeriod);
		i++;
		k++;
        moves++;
	}

	while (j < rightSize) {
		tempArray[k] = tempArrayRight[j];
		sortVisualizer(-1,mid+1+j);
        SDL_Delay(delayPeriod);
		j++;
		k++;
        moves++;
	}

	int tempInd = 0;

	for (int ind = left; ind <= right; ind++, tempInd++) {
		v[ind] = tempArray[tempInd];
		sortVisualizer(ind);
		SDL_Delay(delayPeriod);
	}

}

void mergeSort(vector<int>&v, int startIndex, int endIndex) {
	if (startIndex < endIndex) {
		int midIndex = startIndex + (endIndex - startIndex) / 2;

		mergeSort(v, startIndex, midIndex);
		mergeSort(v, midIndex + 1, endIndex);

		merge(v, startIndex, midIndex, endIndex);
	}

	return;
}

int partition(vector<int>&v, int left, int right){
    int pivot = v[left];
    int i=left, j = right;

    while(i<j){
        while(i<j && v[i]<=pivot){
            i++;
            sortVisualizer(i,j);
            SDL_Delay(delayPeriod);
            moves++;
        }
        while(v[j]>pivot){
            j--;
            sortVisualizer(i,j);
            SDL_Delay(delayPeriod);
            moves++;
        }

        if(i<j) swap(v[i],v[j]);

        sortVisualizer(i,j);
        SDL_Delay(delayPeriod);
    }
    swap(v[left], v[j]);
    sortVisualizer(left,j);
    SDL_Delay(delayPeriod);

    return j;
}

void quickSort(vector<int>&v, int start, int end) {
    if(start<end){
        int index = partition(v,start,end);
        quickSort(v, start, index-1);
        quickSort(v,index+1,end);
    }
}

void heapify(vector<int>&v, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && v[l] > v[largest]) {
		largest = l;
        moves++;
	}

	if (r < n && v[r] > v[largest]) {
		largest = r;
        moves++;
	}

	if (largest != i) {
		swap(v[i], v[largest]);
        sortVisualizer(i,largest);
        SDL_Delay(delayPeriod);
		heapify(v, n, largest);
	}

}

void buildHeap()
{
	for (int i = arrSize / 2 - 1; i >= 0; i--) {
		heapify(storedArray, arrSize, i);
	}

}

void heapSort()
{
	buildHeap();
    SDL_Delay(1000);
	for (int i = arrSize - 1; i > 0; i--) {
		swap(storedArray[0], storedArray[i]);
        sortVisualizer(0,i);
        SDL_Delay(delayPeriod);
		heapify(storedArray, i, 0);
	}

}

void countingSort() {
	int mx = -1;

	for (int i = 0; i < arrSize; i++) {
        while(SDL_PollEvent(&global_ev) != 0){
            if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                close = true;
                return;
            }
        }
		mx = max(mx, storedArray[i]);
	}

	int range = mx + 1;

	vector<int>count(range);

	for (int i = 0; i < arrSize; i++) {
        while(SDL_PollEvent(&global_ev) != 0){
            if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                close = true;
                return;
            }
        }
		count[storedArray[i]]++;
        sortVisualizer(i);
        SDL_Delay(delayPeriod);
	}

	for (int i = 1; i < count.size(); i++) {
        while(SDL_PollEvent(&global_ev) != 0){
            if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                close = true;
                return;
            }
        }
		count[i] += count[i - 1];
	}

	vector<int>output(arrSize);

	for (int i = arrSize - 1; i >= 0; i--) {
        while(SDL_PollEvent(&global_ev) != 0){
            if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                close = true;
                return;
            }
        }
		output[count[storedArray[i]] - 1] = storedArray[i];
        sortVisualizer(count[storedArray[i]] - 1,i);
		count[storedArray[i]]--;
        SDL_Delay(delayPeriod);
	}

	for (int i = 0; i < arrSize; i++){
        while(SDL_PollEvent(&global_ev) != 0){
            if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                close = true;
                return;
            }
        }
        storedArray[i] = output[i];
        sortVisualizer(i);
        SDL_Delay(delayPeriod);
    }
}

void shellSort() {
	for (int gap = arrSize / 2; gap >= 1; gap /= 2) {
        while(SDL_PollEvent(&global_ev) != 0){
            if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                close = true;
                return;
            }
        }
		for (int i = gap; i < arrSize; i++) {
			int temp = storedArray[i];
			int j = i - gap;

			while (j >= 0 && storedArray[j] > temp) {
                while(SDL_PollEvent(&global_ev) != 0){
                    if(global_ev.type == SDL_QUIT || (global_ev.type == SDL_KEYDOWN && global_ev.key.keysym.sym == SDLK_e)){
                        close = true;
                        return;
                    }
                }
                moves++;
				storedArray[j + gap] = storedArray[j];
				sortVisualizer(j, j + gap);
				SDL_Delay(delayPeriod);
				j -= gap;
			}

            if(j!=i-gap) moves++;

			storedArray[j + gap] = temp;
			sortVisualizer(j + gap, -1);
			SDL_Delay(delayPeriod);
		}
	}
}


void showLoadedArray(){
    cout << endl << "Loaded array:  ";
    for(int i=0; i<arrSize; i++){
        cout << storedArray[i] << " \n"[i==arrSize-1];
    }

    cout << "Loaded array size : " << arrSize << endl << endl; 
    return;
}

void showSortedArray() {
    cout << endl << "Sorted Array:  ";

    for(int i=0; i<arrSize; i++){
        cout << storedArray[i] << " \n"[i==arrSize-1];
    }
    cout << endl;

    return;
}
void loadArray(){
    for(int i=0; i<arrSize; i++){
        storedArray[i] = generatedArray[i];
    }
    return;
}

void generateArray(){
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);

    for(int i=0; i<arrSize; i++){
        generatedArray[i] = rand()%screenHeight;
    }
}

bool initializeSDL(){
    bool execute = true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"Video Initialization error: "<<SDL_GetError() << endl;
        return !execute;
    }
    else
    {
        if(!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")))
        {
            cout<<"Linear texture filtering was not enabled" << endl;;
        }

        window=SDL_CreateWindow("Sorting Algorithm Visualizer",
         SDL_WINDOWPOS_CENTERED, 
         SDL_WINDOWPOS_CENTERED, 
         screenWidth, 
         screenHeight, SDL_WINDOW_ALLOW_HIGHDPI);
        if(window==NULL)
        {
            cout<<"Failed to create window: "<<SDL_GetError() << endl;
            return !execute;
        }
        else
        {
            renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                cout<<"Failed to create renderer: " <<SDL_GetError() << endl;
                return !execute;
            }
        }
    }

    return execute;
}

void executeCommand() {
    time_t start,end;
    if(!initializeSDL()){
        cout << "SDL initialization failed" << endl;
    }

    else{
        generateArray();
        loadArray();
        showLoadedArray();

        SDL_Event ev;

        close = false;
        
        while(!close){
            while(SDL_PollEvent(&ev) != 0){
                if(ev.type == SDL_QUIT){
                    close = true;
                    finished = false;
                }

                else if(ev.type == SDL_KEYDOWN){
                    switch(ev.key.keysym.sym){
                        case(SDLK_e):
                            close = true;
                            finished = false;

                            cout << endl << "Exiting Sorting Algorithm Visualizer" << endl;
                            break;
                        
                        case(SDLK_0):
                            generateArray();
                            cout << "New Array Generated" << endl;
                            loadArray();
                            showLoadedArray();
                            finished = false;
                            break;

                        case(SDLK_1):
                            loadArray();
                            cout << "Bubble sort algorithom has started" << endl;

                            finished = false;
                            moves = 0;

                            time(&start);
                            bubbleSort();
                            time(&end);

                            finished = true;

                            cout << "Bubble Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end-start) << endl;
                            cout << "Total comparisons: " << moves << endl;

                            showSortedArray();
                            break;  
                        case(SDLK_2):
                            loadArray();
                            cout << "Insertion Sort Algorithm has started" << endl;

                            finished = false;
                            moves = 0;

                            time(&start);
                            insertionSort();
                            time(&end);

                            finished = true;

                            cout << "Insertion Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end-start) << endl;
                            cout << "Total comparisons: " << moves << endl;

                            showSortedArray();
                            break;

                        case(SDLK_3):
                            loadArray();
                            cout << "Selection Sort Algorithm has started" << endl;

                            finished = false;
                            moves = 0;

                            time(&start);
                            selectionSort();
                            time(&end);

                            finished = true;

                            cout << "Selection Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end-start) << endl;
                            cout << "Total comparisons: " << moves << endl;

                            showSortedArray();
                            break;
                        
                        case(SDLK_4):
                            loadArray();
                            cout << "Merge Sort Algorithm has started" << endl;

                            finished = false;
                            moves = 0;

                            time(&start);
                            mergeSort(storedArray, 0, arrSize-1);
                            time(&end);

                            finished = true;

                            cout << "Merge Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end-start) << endl;
                            cout << "Total comparisons: " << moves << endl;

                            showSortedArray();
                            break;
                        
                        case(SDLK_5):
                            loadArray();
                            cout << "Quick Sort Algorithm has started" << endl;

                            finished = false;
                            moves = 0;

                            time(&start);
                            quickSort(storedArray, 0, arrSize-1);
                            time(&end);

                            finished = true;

                            cout << "Quick Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end-start) << endl;
                            cout << "Total comparisons: " << moves << endl;

                            showSortedArray();
                            break;

                        case(SDLK_6):
                            loadArray();
                            cout << "Heap Sort Algorithm has started" << endl;

                            finished = false;
                            moves = 0;

                            time(&start);
                            heapSort();
                            time(&end);

                            finished = true;

                            cout << "Heap Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end-start) << endl;
                            cout << "Total comparisons: " << moves << endl;

                            showSortedArray();
                            break;
                        
                        case(SDLK_7):
                            loadArray();
                            cout << "Counting Sort Algorithm has started" << endl;

                            finished = false;

                            time(&start);
                            countingSort();
                            time(&end);

                            finished=true;

                            cout << "Counting Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end-start) << endl;
                            cout<< "Total Comparisons: No comparisons required" << endl;
                            
                            showSortedArray();
                            break;

                        case(SDLK_8):
                            loadArray();
                            cout << "Shell Sort Algorithm has started" << endl;
                            
                            finished = false;
                            moves = 0;
                            
                            time(&start);
                            shellSort();
                            time(&end);

                            finished = true;

                            cout << "Shell Sort Completed" << endl;
                            cout << "Time taken: " << (double)(end - start) << endl;
                            cout << "Total Comparisons: " << moves << endl;

                            showSortedArray();
                            break; 
                    }
                }

                if(close){
                    finished = false;
                }
            }
            sortVisualizer();
        }
        quit();
    }
}

bool controlGuide(){
    string sd,sp;
    for(int i=0;i<20;i++){
        sp.push_back(' ');
    }
    for(int i=0; i<30; i++){
        sd.push_back('-');
    }
    cout << endl << sp << sd << "User Guide" << sd ;
    cout << endl << "Press Enter to view the visualizer or -1 to exit the program " << endl;
    cout << "After entering the visualizer: " << endl;
    cout << "Press 0 to generate a new array of integers" << endl;
    cout << "Or" << endl;
    cout << "To perfom a sorting operation on the generated array, press any of the following numbers as mentioned below: " << endl;
    cout << " 1 for Bubble Sort" << endl;
    cout << " 2 for Insertion Sort" << endl;
    cout << " 3 for Selection Sort" << endl;
    cout << " 4 for Merge Sort" << endl;
    cout << " 5 for Quick Sort" << endl;
    cout << " 6 for Heap Sort" << endl;
    cout << " 7 for Counting Sort" << endl;
    cout << " 8 for Shell Sort" << endl;
    cout << endl << "Press e to exit the visualizer" << endl;
    

    string s;
    while(true){
        getline(cin, s);

        if(s.empty()){
            return true;
        }
        else if(s == "-1") return false;

        else cout<< endl << "Please give a valid command" << endl;
    }
}

bool introMessages(){
    string sp,ss;
    for(int i=0;i<20;i++){
        sp.push_back(' ');
    }
    for(int i=0; i<30; i++){
        ss.push_back('*');
    }

    cout << endl << sp << ss << "WELCOME TO SORTING ALGORITHM VISUALIZER" << ss << endl;

    cout << endl << "Press Enter to continue or -1 to exit the program: ";
    string s;
    while(true){
        getline(cin,s);
        if(s.empty()){
            return controlGuide();
        }  
        else if(s == "-1"){
            return false;
        }
        else{
            cout << "Invalid command" << endl;
        }
    }
}

int main(int args, char* argc[]){
    while(true){
        if(introMessages()) {
            executeCommand();
        }

        else{
            cout << endl << "Exiting...Thanks for using the visualizer" << endl;
            break;
        }
    }
}