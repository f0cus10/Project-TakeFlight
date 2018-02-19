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
#include <chrono>

/* To make http requests using REST API */
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>


using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using std::cout;
using std::endl;


int main(int argc, const char * argv[]) {
  auto filestream = std::make_shared<ostream>();
  pplx::task<void> requestTask = fstream::open_ostream(U("result.json")).then([=] (ostream outFile){
    *filestream = outFile;
    http_client client(U("https://opensky-network.org"));
    
    //Build the uri builder and start the request
    uri_builder builder(U("/api/states/all"));
    //TODO (BuildError #1): Need to convert std::chrono::time_t to string to allow making a request
    builder.append_query(U("time"), U(std::chrono::system_clock::now()));
    return client.request(methods::GET, builder.to_string());
  })
  .then([=] (http_response response){
    cout << "Received response code: " << response.status_code() << endl;
    return response.body().read_to_end(filestream->streambuf());
  })
  .then([=] (size_t){
    return filestream->close();
  });
  
  try{
    requestTask.wait();
  }
  catch(const std::exception &e){
    printf("Error Exception:%s\n", e.what());
  }
  return 0;
}

