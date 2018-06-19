{
  'targets': [
    {
      'target_name': 'node-icu-transliterator',
      'sources': [ 'node-icu-transliterator.cpp' ],
      'cflags!': [ '-fno-exceptions', '`pkg-config --cflags icu-i18n`' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'libraries': [ '`pkg-config --libs icu-i18n`' ],
      'include_dirs': [ '<!@(node -p "require(\'node-addon-api\').include")' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7',
        'OTHER_CFLAGS': [ '`pkg-config --cflags icu-i18n`' ]
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      },
    }
  ]
}
