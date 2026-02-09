$path = "$env:TEMP\ViveTool\"
$function1 = "43229420"
$function2 = "27623730"

if (Test-Path $path) {
    Write-Host "ViveTool est installé dans : $path"
    Start-Sleep -Seconds 2
    Write-Host "Lancement de la désactivation de AppDefaultHashRotation... et AppDefaultHashRotationUpdateHashes"
} else {
    Write-Host "ViveTool n'est pas installé, Installation en cours..."
    $repo = "thebookisclosed/ViVe"
    $apiUrl = "https://api.github.com/repos/$repo/releases/latest"

    Write-Host "Récupération de la dernière version de ViveTool..."

    $release = Invoke-RestMethod -Uri $apiUrl -Headers @{
        "User-Agent" = "PowerShell"
    }

    $asset = $release.assets | Where-Object {
        $_.name -match "ViveTool.*\.zip"
    } | Select-Object -First 1

    if (-not $asset) {
        Write-Error "Impossible de trouver l'archive ViveTool."
        exit 1
    }

    $zipPath = "$env:TEMP\$($asset.name)"

    Write-Host "Téléchargement de $($asset.name)..."
    Invoke-WebRequest -Uri $asset.browser_download_url -OutFile $zipPath

    Write-Host "Extraction de ViveTool..."
    Expand-Archive -Path $zipPath -DestinationPath $path -Force

    Write-Host "ViveTool installé dans : $path"
}
Set-Location $path
Start-Sleep -Seconds 2
Write-Host "Verification de la presence des fonctions AppDefaultHashRotation ($function1) et AppDefaultHashRotationUpdateHashes ($function2)..."

# Fonction utilitaire pour vérifier si la feature User est activée
function Is-UserEnabled($featureID) {
    $test = .\ViveTool.exe /query | Select-String -Pattern $featureID -Context 0,4
    # On ne regarde que le scope User
    $enabled = $test | ForEach-Object { $_.Line, $_.Context.PostContext } |
               Where-Object { $_ -match "Priority\s+: User" -and $_ -match "State\s+: Enabled \(2\)" }
    return ($enabled.Count -gt 0)
}

# Vérification et désactivation pour 43229420
if (Is-UserEnabled $function1) {
    Write-Output "La fonctionnalité 43229420 est activée pour User, désactivation..."
    .\ViveTool.exe /disable /id:$function1
    Start-Sleep -Seconds 1
    if (Is-UserEnabled $function1) {
        Write-Output "La fonctionnalité 43229420 est toujours activée pour User"
    } else {
        Write-Output "La fonctionnalité 43229420 a été désactivée pour User"
    }
} else {
    Write-Output "La fonctionnalité 43229420 est déjà désactivée ou absente pour User"
}

# Vérification et désactivation pour 27623730
if (Is-UserEnabled $function2) {
    Write-Output "La fonctionnalité 27623730 est activée pour User, désactivation..."
    .\ViveTool.exe /disable /id:$function2
    Start-Sleep -Seconds 1
    if (Is-UserEnabled $function2) {
        Write-Output "La fonctionnalité 27623730 est toujours activée pour User"
    } else {
        Write-Output "La fonctionnalité 27623730 a été désactivée pour User"
    }
} else {
    Write-Output "La fonctionnalité 27623730 est déjà désactivée ou absente pour User"
}
