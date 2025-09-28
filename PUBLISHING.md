# Publishing Guide

This document explains the automated publishing process for the SimpleModbusSlave library.

## Automated Publishing

The library is automatically published to PlatformIO Registry when:

1. ✅ **All tests pass** (Arduino CLI, PlatformIO, unit tests, validation)
2. ✅ **Branch is `main`** (only releases from main branch)
3. ✅ **Version is newer** than currently published version
4. ✅ **Push event** (not pull request)

## Publishing Process

### 1. Version Management

Update version in **both** files before publishing:

**library.json:**
```json
{
  "version": "1.2.0",
  ...
}
```

**library.properties:**
```properties
version=1.2.0
```

### 2. Automatic Steps

When you push to `main` branch, GitHub Actions will:

1. **Run all tests** - Arduino CLI, PlatformIO, unit tests
2. **Validate library structure** - Check required files and format
3. **Compare versions** - Check if new version > published version
4. **Publish to PlatformIO** - Upload to registry using auth token
5. **Create GitHub Release** - Tag and release with changelog
6. **Update documentation** - Generate installation commands

### 3. Required Secrets

Add these secrets to your GitHub repository:

| Secret Name | Description | How to Get |
|-------------|-------------|------------|
| `PLATFORMIO_AUTH_TOKEN` | PlatformIO account token | [Get from registry.platformio.org/token](https://registry.platformio.org/token) |
| `GITHUB_TOKEN` | GitHub API token | Automatically provided by GitHub Actions |

#### Setting up PlatformIO Token:

1. Go to [https://registry.platformio.org/token](https://registry.platformio.org/token)
2. Login with your PlatformIO account
3. Generate a new token with "Publish" permissions
4. Copy the token
5. Go to your GitHub repository → Settings → Secrets and variables → Actions
6. Click "New repository secret"
7. Name: `PLATFORMIO_AUTH_TOKEN`
8. Value: Your copied token
9. Click "Add secret"

## Version Comparison Logic

The system uses semantic version comparison:

```bash
# Examples of version comparison:
1.0.0 < 1.0.1  ✅ Will publish
1.0.1 < 1.1.0  ✅ Will publish  
1.1.0 < 2.0.0  ✅ Will publish
1.1.0 = 1.1.0  ❌ Will skip
1.1.1 > 1.1.0  ✅ Will publish
2.0.0 > 1.9.9  ✅ Will publish
```

## Manual Publishing (Backup)

If automatic publishing fails, you can publish manually:

### PlatformIO Registry
```bash
# Install PlatformIO
pip install platformio

# Login (one time setup)
pio account login

# Publish from library directory
pio package publish --type=library
```

### Arduino Library Manager
1. Create GitHub release with proper tag (v1.2.0)
2. Arduino will automatically index from GitHub releases
3. Wait 24-48 hours for Arduino Library Manager update

## Troubleshooting

### Publishing Failed

1. **Check version format** - Must be semantic version (1.2.3)
2. **Verify secrets** - PLATFORMIO_AUTH_TOKEN must be valid
3. **Check library structure** - library.json must have required fields
4. **Version conflict** - Ensure new version > published version

### Tests Failed

1. **Arduino compilation** - Fix syntax errors in examples
2. **PlatformIO build** - Check library dependencies
3. **Unit tests** - Fix failing test cases
4. **Validation** - Ensure library.properties has required fields

### Common Issues

| Issue | Solution |
|-------|----------|
| "Version not newer" | Update version in library.json and library.properties |
| "PLATFORMIO_AUTH_TOKEN not found" | Add token to repository secrets |
| "Library validation failed" | Check library.json structure and required fields |
| "Tests failed" | Fix compilation errors in examples or main code |

## Release Notes

Each automatic release includes:

- 📋 **Changelog** - Summary of changes
- 📦 **Installation commands** - PlatformIO and Arduino CLI
- 🔗 **Registry links** - Direct links to library pages  
- ✅ **Test status** - Confirmation all tests passed
- 📊 **Version info** - Current and previous versions

## Best Practices

### Before Publishing

1. ✅ **Test locally** - Build examples on target platforms
2. ✅ **Update version** - Increment version appropriately
3. ✅ **Update documentation** - README, examples, comments
4. ✅ **Run tests** - Ensure all tests pass locally
5. ✅ **Review changes** - Check diff before pushing to main

### Version Strategy

- **Patch (1.0.0 → 1.0.1)** - Bug fixes, small improvements
- **Minor (1.0.1 → 1.1.0)** - New features, backward compatible
- **Major (1.1.0 → 2.0.0)** - Breaking changes, API changes

### Commit Messages

Use clear commit messages for automatic changelog generation:

```
feat: add direction pin support for RS485
fix: resolve static_assert compilation error  
docs: update README with installation instructions
test: add unit tests for CRC validation
```

## Monitoring

Track publishing status:

- 🏃 **GitHub Actions** - Monitor workflow runs in Actions tab
- 📦 **PlatformIO Registry** - Check [registry.platformio.org](https://registry.platformio.org/libraries/kolod/SimpleModbusSlave)  
- 🏷️ **GitHub Releases** - View releases in repository Releases section
- 📊 **Download stats** - Monitor library usage metrics