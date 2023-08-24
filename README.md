# ASBR_Name-ID_Linker
This tool is for the modding of _[JoJo's Bizarre Adventure: All-Star Battle R](https://www.nexusmods.com/jojosbizarreadventureallstarbattler)_, a 2022 game developed by [CyberConnect2](https://jojowiki.com/CyberConnect2).

It takes character string IDs that you input and outputs said characters' short/full names and their integer IDs.

__Why is this useful?__ For note-taking purposes mostly. I personally find it very useful for my ASBR text mods when managing my spreadsheets of data.

If you are new to ASBR modding and want to learn more, join the [JoJo's Bizarre Modding Community on Discord](https://discord.gg/asbr-eoh-modding-community-608029171800735744) and find me `@kojobailey`.

## Installation
1. Download the latest release from the [Releases](https://github.com/KojoBailey/ASBR_Name-ID_Linker/releases/latest) page, or download it from Nexus Mods (coming soon).
2. Ensure that you have `Name-ID_Linker.exe`, `refs.txt`, and `refs_full.txt`. A `settings.cfg` file will automatically be created with default settings when you first run the app.
3. Drag&Drop the file you want to input! Ensure that the formatting is correct by following this guide:

## Usage Guide
### Formatting the input file correctly
The input file is pretty easy to set up. All you need is a list of strings, separated by linebreaks.
The content of the strings doesn't matter as long as the first 6 characters of each line are the ASBR character string IDs (e.g., `4jsk01`).

You can find an example file under the latest release.

### Configuring the tool's settings
This tool only has 2 settings:
1. `delimiter` - CHAR - `,` by default → Determines the delimiter that the output file uses. Commas are fine.
2. `full_names` - BOOL - `0` (false) by default → Toggles whether the output list will use shortened (e.g., Josuke 4) or full (e.g., Josuke Higashikata 4) names.

To change the settings, simply edit the CFG file, but make sure you follow the correct data type requirements.

Note that this tool doesn't allow much flexibility with the formatting of the CFG, so you should only change the parameter values and nothing else (e.g., don't add spaces between the `=` signs!). The only thing you should be good to change is the order of the parameters.

### Inputting a file and recieving the output
As mentioned at the top, all you need to do is drag&drop your single input file onto the EXE.

If successful, the console should output `> Conversion complete! File has been output to 'output.csv'.` and a file titled `output.csv` will appear in the same directory as the EXE.
