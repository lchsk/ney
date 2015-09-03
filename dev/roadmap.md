|Name|Xeon/XeonPhi|vectorisation|parallel|offloading|CUDA|Unit tests|Docs|Wiki|
|---|---|---|---|---|---|---|---|---|
|`vector`|yes|no|no|-||yes|yes|
|`status`|yes|-|-|-||yes|yes|
|`fill`|yes|yes|yes|||yes|yes|
|`config`|yes|-|-|-||yes|yes|
|`time measurement`|yes|-|-|-||yes|yes|
|`random`|yes|yes|yes|||yes|yes|
|`replace`|yes|yes|yes|||yes|yes|
|`reduce`|yes|no|yes|yes||yes|yes|
|`count`|yes|no|yes|yes||yes|yes|
|`apply`|yes|yes|yes|||yes|yes|
|`compare`|yes|yes|yes|||yes|yes|
|`slicing`|yes|-|-|yes||yes|yes|
|`swap`|yes|yes|yes|||yes|yes||
|`sort`|yes|yes|no*|||yes|yes||
|`unique`|yes|no|no|||yes|yes|
|`open`|yes|no|-|-||yes|yes|
|`group_by`|
|`reduce_by`|

####Stuff:

|What|Done|
|---|---|
|vector (copy constructor, =, destructor)|yes|
|status default constructor, printing out|yes|
|a separate class for timing|yes|
|global timer (clock)|yes|
|parallel file opening||
|matrix||
|map||
|mergesort|yes|
|adding two vector|yes|
|compile with gcc|yes|
|`condition` in `base_operation`|yes|
|read number of phis|yes|
|sequence||
|fabs in comparisons|yes|
|std::string as T||
|validation of parameters|yes|
|conditional `swap`|yes|
|single vector bitonic sort||
|GPU vector||
|at least one function on GPU||
|bitonic sort performance measurement||
|GPU/Xeon/Xeon Phi measurements||


#### Tools

|Tool|Done|
|---|---|
|vectorisation reports (automatic generation)|yes|
|python validator|yes|
|aligned access|yes|

#### Examples

|Algorithm|Done|
|---|---|
|Character count|yes|
|Words count|yes|
|Word occurences||
|Bitonic sort|yes|
|SAXPY|yes|
|Weld triangles|yes|
|Run-length encoding|yes|
|PI estimation|yes|
|Image effects|yes|
|Particles simulation|yes|
