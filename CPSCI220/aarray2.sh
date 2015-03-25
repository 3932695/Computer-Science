declare -A states2
states1=("California" "New York" "Nevada" "Utah")
states2=( ["CA"]="California" ["NY"]="New York" ["NV"]="Nevada" ["UT"]="Utah")
ind1=0
ind2=CA
echo "1. \${states1[ind1]} = ${states1[ind1]}"
echo "2. \${states2[ind2]} = ${states2[ind2]}"
echo "3. \${states2[\$ind2]} = ${states2[$ind2]}"
