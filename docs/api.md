# API Usage

[TOC]

The ROS2Sonic metapackage contains the r2sonic package and the r2sonic_interface packages.   The r2sonic package contains the libraries and executable needed to parse the data formats described by the R2Sonic Data Format definition document.

## Getting Started 

### Parsing Packets

Let's assume you have a character array `char * buffer;` containing a data packet received from your R2Sonic unit.   You likely received this from a UDP receiver of some kind.  

In the Uplink Data Formats Document you can see a description of the packets available.  The `r2sonic::packets` namespace contains decoders for each type packet.

Each type is based on the `r2sonic::packets::Packet` class. 

Let's say we want to decode BTH0 message.  We can use the corresponding packet decoder `r2sonic::packets::BTH0` which, like all uplink datatype decoders, is derived from the `r2sonic::packets::Packet` class. 


here's an example of how to use it.    

```
  // char * buffer;  // we assume this is filled earlier in the code
  r2sonic::packets::BTH0 packet(buffer);

  if(packet.isType()){  // check to make sure the buffer actually 
  						// contains a r2sonic::packets::BTH0 message
  	// we can now access the various members!
  }
```

`r2sonic::packets` generally contain several `r2sonic::sections`.  You can review the API documentation for details on those specific members.  Many `r2sonic::packets` have optional `r2sonic::sections`.   Before you attempt to access any of the data in the packet on optional sections make sure you check their existence with `r2sonic::sections::Section::exists`.

Now that we can access the `r2sonic::sections` we need to access the individual fields.  R2Sonic delivers their data in big-endian format.  This may need to be converted to be processed on your machine.   To represent this data the `r2sonic::primitives::BigEndianPrimative< PrimT >` structure is used.  A list of primitive typedefs can be found in the `r2sonic::primitives` namespace documentation.

The `r2sonic::BigEndianPrimative< PrimT >::get` method can be used to get a machine readable version of the variable.   Alternatively, you can simply use the equals operator like so `r2sonic::primitives::BE_u8 be_x;`  `int x = be_x;`.

Let's update our code with some access examples.

```
  r2sonic::packets::BTH0 packet(buffer);

  if(packet.isType()){ 
  	unsigned int ping = packet.h0->body.PingNumber;
  	if(packet.i1.exists()){ // i1 is an optional section in the bth0 packet.
  	  packet.i1.Intensity(0)->get();
  	}
  }
```