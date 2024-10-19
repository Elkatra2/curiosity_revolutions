base=tests/terrain_11x9

largeur_base=$base"_largeur"
hauteur_base=$base"_hauteur"
terrain_base=$base"_terrain"

test_terrain2() {
    ./test_terrain $1".test" <<< q
}

# erreurs de largeur
test_terrain2 $largeur_base"_eof"
test_terrain2 $largeur_base"_negatif"
test_terrain2 $largeur_base"_trop_grand"

# erreurs de l'hauteur
test_terrain2 $hauteur_base"_eof"
test_terrain2 $hauteur_base"_negatif"
test_terrain2 $hauteur_base"_trop_grand"

# erreurs du terrain
test_terrain2 $terrain_base"_eof"
test_terrain2 $terrain_base"_largeur"
test_terrain2 $terrain_base"_hauteur"
test_terrain2 $terrain_base"_curiosity_deux"
test_terrain2 $terrain_base"_curiosity_disparait"

# erreurs du fichier
test_terrain2 $base"_fichier_grand"

# autre erreurs
test_terrain2 "tests/terrain_11x9"
test_terrain2 "tests/terrain_256x1"