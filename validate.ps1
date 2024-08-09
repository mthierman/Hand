Push-Location
Set-Location build/examples/basic/Debug
clap-validator validate .\BasicPlugin.clap
Pop-Location

Push-Location
Set-Location build/examples/gui/Debug
clap-validator validate .\GuiPlugin.clap
Pop-Location
