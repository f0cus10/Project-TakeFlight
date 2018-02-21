//
//  main.cpp
//  takeflight
//
//  Created by Iftikhar Khan on 2/19/18.
//  Copyright © 2018 Iftikhar Khan. All rights reserved.
//

#include <iostream> //To print to stdin

/* To get current time data */
#include <ctime>
#include <string>


/* To make http requests using REST API */
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace web::json;

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::make_shared;
using std::exception;
/*
 Returns: a string containing the current time
*/
string currentTime(){
  using std::time_t;
  using std::time;
  using std::localtime;
  using std::to_string;
  //Initialise to a nullptr, since the pointer will be passed on to the function
  time_t result = time(nullptr);
  localtime(&result);
  return to_string(result);
}

int main(int argc, const char * argv[]) {
  //Open a filestream to save the response in
  auto fileStream = make_shared<ostream>();
  //Opening a raw byte stream (ostream from concurrency) to results.html
  //Async, b/c it might block iostream (i.e. task-based asynchronous programming) .then() is added to be called as soon as the task is complete
  pplx::task<void> requestTask = fstream::open_ostream(U("/Users/ifti/Downloads/results.json")).then([=] (ostream outFile){
    *fileStream = outFile;
    
    //We create a http_client to send the http request
    http_client client{U("https://opensky-network.org/api/states/")};
    //Builder request uri and start the request
    uri_builder builder{U("/all")};
    //Add the query to the end to formulate something like this "client/builder?appended[0]=appended[1]"
    builder.append_query(U("time"), U(currentTime()));
    
    //Make a get request using the uri
    return client.request(methods::GET, builder.to_string());
  })
  //Handle responses arriving
  .then([=] (http_response response){
    cout << "Received response code: " << response.status_code() << endl;
    
    //Take the responses and write them to the file
    return response.body().read_to_end(fileStream->streambuf());
  })
  .then([=] (size_t){
    return fileStream->close();
  });
  try{
    requestTask.wait();
  }
  catch(const exception &e){
    cout << "Error Exception: " << e.what() << endl;
  }
  
  return 0;
}

