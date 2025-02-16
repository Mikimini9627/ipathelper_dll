using System.Runtime.InteropServices;
using System.Reflection;

// このような SDK スタイルのプロジェクトの場合、以前はこのファイルで定義していたいくつかのアセンブリ属性がビルド時に自動的に追加されて、プロジェクトのプロパティで定義されている値がそれに設定されるようになりました。組み込まれる属性と、このプロセスをカスタマイズする方法の詳細については、次を参照してください:
// https://aka.ms/assembly-info-properties

#if x64
[assembly: AssemblyTitle("IpatHelper-CSharp x64")]
[assembly: AssemblyDescription("IpatHelper-CSharp x64")]
[assembly: AssemblyProduct("IpatHelper-CSharp x64")]
#else
[assembly: AssemblyTitle("IpatHelper-CSharp x86")]
[assembly: AssemblyDescription("IpatHelper-CSharp x86")]
[assembly: AssemblyProduct("IpatHelper-CSharp x86")]
#endif
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("Mikimini")]
[assembly: AssemblyCopyright("Copyright © HP Inc. 2023 Mikimini9627")]
[assembly: AssemblyInformationalVersion("2.0.0.0")]
[assembly: AssemblyFileVersion("2.0.0.0")]

// ComVisible を false に設定すると、このアセンブリ内の型は COM コンポーネントから参照できなくなります。このアセンブリ内の型に COM からアクセスする必要がある場合は、その型の
// ComVisible 属性を true に設定してください。

[assembly: ComVisible(false)]

// このプロジェクトが COM に公開される場合、次の GUID が typelib の ID になります。

[assembly: Guid("e548c1ca-0928-44e3-91fe-a0d7ea2ea9f7")]
