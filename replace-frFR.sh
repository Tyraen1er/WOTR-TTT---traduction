#!/bin/sh

SOURCE="francais_seulement.json"
CIBLE="LocalizationPack.json"
TEMP_EXTRACT="lines_fr.tmp"
RESULTAT="LocalizationPack_final.json"

grep "^      \"frFR\":" "$SOURCE" > "$TEMP_EXTRACT"

exec 3< "$TEMP_EXTRACT"

while IFS= read -r line; do
    case "$line" in
        "      \"frFR\":"*)
            if IFS= read -r new_line <&3; then
                printf "%s\n" "$new_line"
            else
                printf "%s\n" "$line"
            fi
            ;;
        *)
            printf "%s\n" "$line"
            ;;
    esac
done < "$CIBLE" > "$RESULTAT"

exec 3<&-
rm "$TEMP_EXTRACT"
mv "$RESULTAT" "$CIBLE"
