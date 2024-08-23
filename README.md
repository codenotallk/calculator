# Calculator

This is a project to help me to implement a simple Microservice.
The context is quite simple. It will be a simple calculator. 
The domain must be easy the grasp. The focus here is how to use all the important
techniques to reach the goal.

In the first step I'll work with a server and a browser or a curl as a client.
I'll set two endpoints: one to calculate and the another to get these calculations.

In the second part I'll store every calculation in a file
In the third part I'll change the file persistency to a database MySQL in that case.
In the fifth part I'll split the server in two servers. One to calculate and the another
to receive the requests to get data.
in the sixth part I'll join the two servers in the same endpoint again using a reverse proxy.
In the seventh part I'll change the architecture to a EDA. Event driven Architecture. hehe. Here I'll use kafka. And for consume these messages a new service will be created.

Finally in the part eigth I'll create a new service using push bullet service to notify the user.

I'll divide in steps the track the evolution.

## Part 1 - Step 1 - Create a server with a health endpoint.

To make things easier. I'll create a library to encapsulate the answer (response).
Now I have a common send.

Now I have the server running. Now the next step is add a endpoint calculate. Bye


## Part 1 - Step 2 - Create the calculate endpoint.

I'm still in the step 1, but I will implement the calculate endpoint 
To receive the message I'll create a DTO (Data Transfer Object).

It's just performing a plus operation. or sum operation. that's it. bye.

## Part 1 - Step 3 - Adding the operations
The server is capable to perform just a sum operation. I'll add all four basic operations.
For that I need to create the operation and do some refactor.
Now I'll refactor the operation_request

At this point I need a response object.

Now the server can perform the basic operations, sum, subb, multiply and divide. that's it. bye.

## Part 2 - Step 4 - Adding repository - persistence by file

Before create the endpoint to consult all the operations already did. I need to add repository first. The layout will start that way.

Now each request will be persisted.
Now I can retrieve all these registers. that's it.

## Part 2 - Step 5 - Adding Report Endpoint.

Now I set up the step necessary to retrieve data. I keep with the same configuration.

Right. I can get the data from database and obtain all of them from report endpoint.
That's it.

## Part 2 - Step 6 - Testing input from request

The last step I forgot to implement th offset for repository.

Now I can perform offset. I didn't set a verification for inputs that I receive. So Let's protect the application against those parameters that can be bad formed.

I faced a little problem, but it is working now. Bye

## Part 3 - Step 7 - Moving to a database engine

I did all the persistence in Files. Well, files aren't the best way to persist a lot of data.
So, I will change from file to database. In that case, it'll be a MySQL database.

First things first. I don't want to lose all the job already did. So, First I'll extract the functions signatures into a interface. That way, I can inject the database of my choice.
With that, I avoid to thrown away my job. 

I have some goals for that: 
* extract in a interface
* add the MySQL database using docker compose
* Implement the MySQL persistence.

I already have the interface working as intended.
Now I implement the docker compose to rise up the database.

We already have the database working through docker.
Next step is implement the mysql 

Finally. Sometimes problems arise. That's life programming. The base implementation. It was done. Next I'll finish retrieve data from database. That's it.

## Part 3 - Step 8 - Retrieving data from database

In the step 7 I did a mistake. I was thinking the database and the application were inside the docker environment. That's the why the connection didn't work.

Ok, Back on the rails. I will implement now the retrieving data using filters specifying the period.

Now I need to open a connection. I'll create an auxiliary function to open. So I can use it
in other contexts.

To get data from database. It's necessary to scan each row retrieved from result set operation. To make things easier, I'll create a enum to mark the items position or columns.

Ok!!! I have implemented the retrieve. Now let's add the filter. For that I need to create 
another DTO for receive parameters from url to build the query based on these parameters.

To handle this DTO inside the application I need another object.

Phew!!! Finally finished. Now I can filter request from report data. That's it.