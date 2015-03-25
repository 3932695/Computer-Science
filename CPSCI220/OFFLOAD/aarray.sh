declare -A states
states=( ["CA"]="California" ["NY"]="New York" )
echo "You entered: ${states[${1}]}"
