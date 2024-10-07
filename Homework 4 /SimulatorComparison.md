# Compare with Gadot's MLFQ (https://github.com/iamgodot/5600/blob/main/hw3/mlfq.c)

I defined specific quantums for each queue and integrated a mechanism to handle idle times and determine how processes move between queues. Grant charts are used for more precise tracking of process states.
The design of Queue02 that implements LRTF is not practical in reality.

 The boosting policy in Godot's code is clear and straightforward, with a regular interval boost (BOOST_INTERVAL) that moves all processes to the highest priority queue. It appears simpler but could be less flexible in handling different scenarios, as all processes are boosted uniformly without considering their runtime characteristics.
