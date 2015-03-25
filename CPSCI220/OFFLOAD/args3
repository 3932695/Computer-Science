echo "\$@        = $@"
start=2
count=3
echo "\${@:2}    = ${@:$start}"
echo "\${@:2:3}  = ${@:$start:$count}"

start=-4
echo "\${@:-4}   = ${@:$start}"
echo "\${@:-4:3} = ${@:$start:$count}"

# Use in for loop
echo "Looping range of arguments"
for i in "${@:$start:$count}"
do
 echo "$i"
done
