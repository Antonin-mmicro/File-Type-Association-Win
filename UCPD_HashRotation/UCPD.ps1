try {
    Set-Service -Name UCPD -StartupType Disabled
    Disable-ScheduledTask -TaskName "\Microsoft\Windows\AppxDeploymentClient\UCPD velocity"
    Write-Host "Le service UCPD a été désactivé et la tâche planifiée associée a été désactivée."
}
catch {
    Write-Host "Le service UCPD n'existe pas ou une erreur est survenue : $_"
}