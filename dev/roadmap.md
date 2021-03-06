|Name|Xeon/XeonPhi|vectorisation|parallel|offloading|Unit tests|Docs|
|---|---|---|---|---|---|---|---|---|
|`vector`|yes|no|no|-|yes|yes|
|`status`|yes|-|-|-|yes|yes|
|`fill`|yes|yes|yes||yes|yes|
|`config`|yes|-|-|-|yes|yes|
|`time measurement`|yes|-|-|-|yes|yes|
|`random`|yes|yes|yes||yes|yes|
|`replace`|yes|yes|yes||yes|yes|
|`reduce`|yes|no|yes|yes|yes|yes|
|`count`|yes|no|yes|yes|yes|yes|
|`apply`|yes|yes|yes||yes|yes|
|`compare`|yes|yes|yes||yes|yes|
|`slicing`|yes|-|-|yes|yes|yes|
|`swap`|yes|yes|yes||yes|yes|
|`sort`|yes|yes|no*||yes|yes|
|`unique`|yes|no|no||yes|yes|
|`open`|yes|no|-|-|yes|yes|

|Name|CUDA|Unit tests|
|---|---|---|---|---|---|---|---|---|
|`vector`|yes|yes|
|`status`|yes||
|`fill`|yes|yes|
|`config`|yes||
|`time measurement`|yes||
|`random`|yes|yes|
|`replace`|yes|yes|
|`reduce`|yes|yes|
|`count`|yes|yes|
|`apply`|yes|yes|
|`compare`|
|`slicing`|yes|yes|
|`swap`|
|`sort`|yes|yes|
|`unique`|yes|yes|
|`open`|yes|yes|

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
|GPU vector|yes|
|at least one function on GPU|yes|
|bitonic sort performance measurement||
|GPU/Xeon/Xeon Phi measurements||
|Fix examples (`.set()`)|yes|


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
