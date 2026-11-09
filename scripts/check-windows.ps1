param(
  [string[]]$Presets = @(
    'win-msvc-debug', 'win-msvc-release',
    'win-clang-debug', 'win-clang-release', 'win-clang-debug-tidy'
  )
)

Set-Location (Split-Path -Parent $PSScriptRoot)

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vs = & $vswhere -latest -products * -property installationPath
if (-not $vs) { Write-Error 'Visual Studio not found'; exit 1 }
Import-Module "$vs\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
Enter-VsDevShell -VsInstallPath $vs -SkipAutomaticLocation -DevCmdArguments '-arch=x64' | Out-Null

$passed = @()
$failed = @()

foreach ($p in $Presets) {
  Write-Host "`n=== $p ===" -ForegroundColor Cyan
  cmake --workflow --preset $p
  if ($LASTEXITCODE -eq 0) { $passed += $p } else { $failed += $p }
}

Write-Host "`n=== Summary ===" -ForegroundColor Cyan
Write-Host "PASS: $($passed -join ' ')" -ForegroundColor Green
Write-Host "FAIL: $($failed -join ' ')" -ForegroundColor Red
exit $failed.Count
