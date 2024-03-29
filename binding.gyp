{
  'targets': [
    {
      'target_name': 'oniguruma',
      'sources': ['src/binding.cc', 'src/node_oniguruma.cc'],
      'cflags': ['-fexceptions'],
      'cflags_cc': ['-fexceptions'],
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exception'],
      'libraries': ['-lonig'],
      'conditions': [
        ['OS=="win"', {
            'msvs_settings': {
              'VCCLCompilerTool': {
                'AdditionalOptions': [ '/EHsc' ]
              }
            }
          }
        ],
        ['OS=="mac"', {
            'xcode_settings': {
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
            }
          }
        ]
      ]
    }
  ]
}