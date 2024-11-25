
# Getting Started with Avalonia on macOS

## 1. Prerequisites
Ensure the following are installed on your macOS system:

- **.NET SDK**: Download and install the latest version of the [.NET SDK](https://dotnet.microsoft.com/download).
  ```bash
  dotnet --version
  ```
  Use this command to verify the installation.

- **IDE**: Install a code editor or IDE such as:
  - [Visual Studio for Mac](https://visualstudio.microsoft.com/vs/mac/)
  - [JetBrains Rider](https://www.jetbrains.com/rider/)
  - [Visual Studio Code](https://code.visualstudio.com/)

- **Xcode**: Install Xcode via the Mac App Store to ensure you have all the required build tools and SDKs.

---

## 2. Install Avalonia Templates
Avalonia provides project templates to quickly scaffold new applications.

Run this command to install the templates:
```bash
dotnet new install Avalonia.Templates
```

You can verify the templates are installed by running:
```bash
dotnet new list
```

Look for `avalonia.app` and related templates in the list.

---

## 3. Create a New Avalonia Application
Generate a new Avalonia app using the template:

```bash
dotnet new avalonia.app -o MyAvaloniaApp
```

Navigate into the project folder:
```bash
cd MyAvaloniaApp
```

---

## 4. Build and Run Your Application
To build and run your Avalonia app:

```bash
dotnet run
```

This will launch the Avalonia application, displaying a basic window.

---

## 5. Development Workflow

### Use Avalonia Previewer
The Avalonia Previewer allows real-time design and layout adjustments for your XAML files:
1. Open the project in an IDE like Visual Studio or Rider.
2. Make sure the Avalonia Previewer plugin is installed.
   - For Rider: Search for "Avalonia" in the Plugin Marketplace.
   - For Visual Studio: Download the [Avalonia VS Extension](https://marketplace.visualstudio.com/items?itemName=AvaloniaTeam.AvaloniaforVisualStudio).

### Edit XAML and C#
- XAML files define your UI layout.
- C# code-behind files handle the app logic.

---

## 6. Optional: Add Dependencies
To add dependencies like NuGet packages for specific features, use:

```bash
dotnet add package <PackageName>
```

For example:
```bash
dotnet add package Avalonia.Dialogs
```

---

## 7. Publish Your Application
When your application is ready for distribution, publish it using:

```bash
dotnet publish -c Release -r osx-x64 --self-contained
```

This creates a self-contained macOS app bundle.

---

## 8. Avalonia Documentation
For more detailed information, refer to the official Avalonia documentation:  
[Avalonia Docs](https://docs.avaloniaui.net)
